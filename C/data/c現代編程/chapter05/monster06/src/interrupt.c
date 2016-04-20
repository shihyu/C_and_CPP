#include <stdbool.h>
#include "hw.h"

#include "interrupt.h"

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

int isTimer3Overflow(void) {
    return PIR2bits.TMR3IF != 0;
}

void MOCKABLE(onUsartInterrupt)(void) {
    if (isUsartOverrunOccurred()) {
        resetUsartPort();
    }
    else {
        int c = USART_RECEIVE_CHAR();
        PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, (char) c);
    }
}

void MOCKABLE(onTimer3Interrupt)(void) {
    int c;
    if ((c = getCharFromRingBuffer(&ringBufferForLcd)) == LCD_DATA_EOF) {
        disableTime3Interrupt();
    }
    else {
        processLcdData(c);
    }
}

void MOCKABLE(resetUsartPort)(void) {
    enableUsartReceiveBuffer(false);
    clearUsartReceiveBuffer();
    enableUsartReceiveBuffer(true);
}

void MOCKABLE(processLcdData)(int c) {
    if (c == LCD_ESCAPE_CHAR) {
        performLcdControl();
    } else {
        performLcdData(c);
    }
}

void disableTime3Interrupt(void) {
    PIE2bits.TMR3IE = 0;
}

void set46msToTimer3(void) {
    // 65536 - 46micro sec / 0.666666
    TMR3H = (65467u >> 8);
    TMR3L = (65467u & 0xff);
}

void clearTimer3Overflow(void) {
    PIR2bits.TMR3IF = 0;
}

void setLcdMode(int mode) {
    PORTBbits.RB0 = mode;
}

void MOCKABLE(performLcdControl)(void) {
    int c = getCharFromRingBuffer(&ringBufferForLcd);
    setLcdMode(LCD_MODE_CONTROL);
    write1byteToLcd(c);
    clearTimer3Overflow();
    set46msToTimer3();
}

void MOCKABLE(performLcdData)(int c) {
    setLcdMode(LCD_MODE_DATA);
    write1byteToLcd(c);
    clearTimer3Overflow();
    set46msToTimer3();
}

void MOCKABLE(write1byteToLcd)(int c) {
    setLcdPortRw(LCD_PORT_WRITE);
    
    setPortA(upper4bitOf(c));
    pulseLcdCe();

    setPortA(lower4bitOf(c));
    pulseLcdCe();
}

int upper4bitOf(int c) {
    return c >> 4;
}

int lower4bitOf(int c) {
    return c & 0xf;
}

#ifdef UNIT_TEST
void (*pResetUsartPort)(void) = MOCKABLE(resetUsartPort);
void resetUsartPort(void) {
    return pResetUsartPort();
}

void (*pWrite1byteToLcd)(int) = MOCKABLE(write1byteToLcd);
void write1byteToLcd(int c) {
    pWrite1byteToLcd(c);
}

void (*pPerformLcdControl)(void) = MOCKABLE(performLcdControl);
void performLcdControl(void) {
    pPerformLcdControl();
}

void (*pPerformLcdData)(int) = MOCKABLE(performLcdData);
void performLcdData(int c) {
    pPerformLcdData(c);
}

void (*pProcessLcdData)(int) = MOCKABLE(processLcdData);
void processLcdData(int c) {
    pProcessLcdData(c);
}

void (*pOnUsartInterrupt)(void) = MOCKABLE(onUsartInterrupt);
void onUsartInterrupt(void) {
    return pOnUsartInterrupt();
}

void (*pOnTimer3Interrupt)(void) = MOCKABLE(onTimer3Interrupt);
void onTimer3Interrupt(void) {
    return pOnTimer3Interrupt();
}
#endif
