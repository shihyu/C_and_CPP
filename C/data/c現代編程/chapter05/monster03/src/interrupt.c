#include "hw.h"
#define UNIT_TEST

#include "interrupt.h"

unsigned int isUsartOverrunOccurred(void) {
    return RCSTAbits.OERR;
}

void resetUsartPort(void) {
    RCSTAbits.CREN = 0;
    // ポートを空読みする。
    int c = USART_RECEIVE_CHAR();
    RCSTAbits.CREN = 1;
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

void disableTime3Interrupt(void) {
    PIE2bits.TMR3IE = 0; // 割込禁止
}

void processLcdData(int c) {
    if (c == (BYTE) 0xFE) { // エスケープ文字
        performLcdControl(c);
    } else {
        performLcdData(c);
    }
}

void lowPriorityISRCode(void) {
    if (isUsartInterruptOccurred()) {
        onUsartInterrupt();
    }
    else if (isTimer3Overflow()) {
        onTimer3Interrupt();
    }
}

unsigned int MOCKABLE(isUsartInterruptOccurred)(void) {
    return PIR1bits.RCIF;
}

#ifdef UNIT_TEST
unsigned int (*pIsUsartInterruptOccurred)(void) = MOCKABLE(isUsartInterruptOccurred);
unsigned int isUsartInterruptOccurred(void) {
    return pIsUsartInterruptOccurred();
}
#endif

void MOCKABLE(onUsartInterrupt)(void) {
    if (isUsartOverrunOccurred()) {
        resetUsartPort();
    } else {
        int c = USART_RECEIVE_CHAR();
        PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, (char) c);
    }
}

#ifdef UNIT_TEST
void (*pOnUsartInterrupt)(void) = MOCKABLE(onUsartInterrupt);
void onUsartInterrupt(void) {
    return pOnUsartInterrupt();
}
#endif

int MOCKABLE(isTimer3Overflow)(void) {
    return PIR2bits.TMR3IF != 0;
}

#ifdef UNIT_TEST
int (*pIsTimer3Overflow)(void) = MOCKABLE(isTimer3Overflow);
int isTimer3Overflow(void) {
    return pIsTimer3Overflow();
}
#endif

void MOCKABLE(onTimer3Interrupt)(void) {
    int c;
    if ((c = getCharFromRingBuffer(&ringBufferForLcd)) != -1) {
        processLcdData(c);
    } else {
        disableTime3Interrupt();
    }
}

#ifdef UNIT_TEST
void (*pOnTimer3Interrupt)(void) = MOCKABLE(onTimer3Interrupt);
void onTimer3Interrupt(void) {
    return pOnTimer3Interrupt();
}
#endif
