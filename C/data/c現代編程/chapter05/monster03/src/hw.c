#include "hw.h"

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
