#include "hw.h"
#include "interrupt.h"

unsigned int isUsartInterruptOccurred(LowPriorityInterrupt *pThis) {
    return PIR1bits.RCIF;
}

unsigned int isUsartOverrunOccurred(LowPriorityInterrupt *pThis) {
    return RCSTAbits.OERR;
}

int isTimer3Overflow(LowPriorityInterrupt *pThis) {
    return PIR2bits.TMR3IF != 0;
}

void resetUsartPort(void) {
    RCSTAbits.CREN = 0;
    // ポートを空読みする。
    int c = USART_RECEIVE_CHAR();
    RCSTAbits.CREN = 1;
}

void onUsartInterrupt(LowPriorityInterrupt *pThis) {
    if (isUsartOverrunOccurred(pThis)) {
        resetUsartPort();
    } else {
        int c = USART_RECEIVE_CHAR();
        PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, (char) c);
    }
}

void write1byteToLcd(int c) {
    PORTBbits.RB2 = 0; // R/W = Write
    // upper 4 bit
    PORTA = c >> 4;
    PORTBbits.RB1 = 1; // CE = enable
    PORTBbits.RB1 = 1;
    PORTBbits.RB1 = 1; // wait 300ns
    PORTBbits.RB1 = 0; // CE = disable
    PORTBbits.RB1 = 0; // wait 200ns
    // lower 4bit
    PORTA = c & 0xf;
    PORTBbits.RB1 = 1; // CE = enable
    PORTBbits.RB1 = 1;
    PORTBbits.RB1 = 1; // wait 300ns
    PORTBbits.RB1 = 0; // CE = disable
}

void performLcdControl(int c) {
    c = getCharFromRingBuffer(&ringBufferForLcd);
    PORTBbits.RB0 = 0; // control mode
    write1byteToLcd(c);
    PIR2bits.TMR3IF = 0; // timer3 オーバーフローをクリア
    // 65536 - 40micro sec / 0.666666
    TMR3H = (65467u >> 8);
    TMR3L = (65467u & 0xff);
}

void performLcdData(int c) {
    PORTBbits.RB0 = 1; // data mode
    write1byteToLcd(c);
    PIR2bits.TMR3IF = 0; // timer3 オーバーフローをクリア
    // 65536 - 46micro sec / 0.666666
    TMR3H = (65467u >> 8);
    TMR3L = (65467u & 0xff);
}

void processLcdData(int c) {
    if (c == (BYTE) 0xFE) { // エスケープ文字
        performLcdControl(c);
    } else {
        performLcdData(c);
    }
}

void disableTime3Interrupt(void) {
    PIE2bits.TMR3IE = 0; // 割込禁止
}

void onTimer3Interrupt(LowPriorityInterrupt *pThis) {
    int c;
    if ((c = getCharFromRingBuffer(&ringBufferForLcd)) != -1) {
        processLcdData(c);
    } else {
        disableTime3Interrupt();
    }
}

static LowPriorityInterrupt lowPriorityInterrupt = {
    isUsartInterruptOccurred,
    onUsartInterrupt,
    isTimer3Overflow,
    onTimer3Interrupt
};

void lowPriorityISRCode(void) {
    performLowPriorityInterrupt(&lowPriorityInterrupt);
}

void performLowPriorityInterrupt(LowPriorityInterrupt *pThis) {
    if (pThis->isUsartInterruptOccurred(pThis)) {
        pThis->onUsartInterrupt(pThis);
    }
    else if (pThis->isTimer3Overflow(pThis)) {
        pThis->onTimer3Interrupt(pThis);
    }
}
