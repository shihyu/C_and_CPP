#include <assert.h>
#include "hw.h"

#ifdef UNIT_TEST
unsigned int usartOverrunFlag;
#endif

unsigned int isUsartOverrunOccurred(void) {
  return RCSTAbits.OERR;
}

#ifdef UNIT_TEST
int usartReceiveBufferEnabledIdx;
bool usartReceiveBufferEnabled[8];
#endif
void enableUsartReceiveBuffer(bool enable) {
#ifdef UNIT_TEST
    assert(usartReceiveBufferEnabledIdx <
           sizeof(usartReceiveBufferEnabled) / sizeof(usartReceiveBufferEnabled[0]));
    usartReceiveBufferEnabled[usartReceiveBufferEnabledIdx++] = enable;
#else
    RCSTAbits.CREN = enable ? 1 : 0;
#endif
}

#ifdef UNIT_TEST
int clearUsartReceiveBufferCallCount;
#endif
void clearUsartReceiveBuffer(void) {
#ifdef UNIT_TEST
    ++clearUsartReceiveBufferCallCount;
#else
    // ポートを空読みする。
    int c = USART_RECEIVE_CHAR();
#endif
}

void setLcdPortRw(int rw) {
    PORTBbits.RB2 = rw;
}

#ifdef UNIT_TEST
int portAIdx;
int portAState[8];
#endif
void setPortA(int data) {
#ifdef UNIT_TEST
    assert(portAIdx <
           sizeof(portAState) / sizeof(portAState[0]));
    portAState[portAIdx++] = data;
#else
    PORTA = data;
#endif
}

#ifdef UNIT_TEST
int pulseLcdCeCallCount;
#endif
void pulseLcdCe(void) {
#ifdef UNIT_TEST
    ++pulseLcdCeCallCount;
#else
    PORTBbits.RB1 = 1; // CE = enable
    PORTBbits.RB1 = 1;
    PORTBbits.RB1 = 1; // wait 300ns
    PORTBbits.RB1 = 0; // CE = disable
    PORTBbits.RB1 = 0; // wait 200ns
#endif
}

PIR1bits_t PIR1bits;
RCSTAbits_t RCSTAbits;
PIR2bits_t PIR2bits;
PIE2bits_t PIE2bits;
BYTE PORTA;
BYTE TMR3H;
BYTE TMR3L;
PORTBbits_t PORTBbits;

RingBuffer ringBufferForReceive;
RingBuffer ringBufferForLcd;

int getCharFromRingBuffer(RingBuffer *p) {
    return 0;
}

int USART_RECEIVE_CHAR(void) {
    return 0;
}

void PUT_CHAR_TO_RING_BUFFER(RingBuffer *p, int c) {
}
