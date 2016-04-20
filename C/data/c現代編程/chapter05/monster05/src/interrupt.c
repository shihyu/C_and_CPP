#include <stdbool.h>
#include "hw.h"

#include "interrupt.h"

void resetUsartPort(void) {
    enableUsartReceiveBuffer(false);
    clearUsartReceiveBuffer();
    enableUsartReceiveBuffer(true);
}

int upper4bitOf(int c) {
    return c >> 4;
}

int lower4bitOf(int c) {
    return c & 0xf;
}

void write1byteToLcd(int c) {
    setLcdPortRw(LCD_PORT_WRITE);
    
    setPortA(upper4bitOf(c));
    pulseLcdCe();

    setPortA(lower4bitOf(c));
    pulseLcdCe();
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

unsigned int isUsartInterruptOccurred(void) {
    return PIR1bits.RCIF;
}

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
