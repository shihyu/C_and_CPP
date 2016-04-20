#ifndef _HW_H_
#define _HW_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned int isUsartOverrunOccurred(void);

#ifdef UNIT_TEST
extern int usartReceiveBufferEnabledIdx;
extern bool usartReceiveBufferEnabled[8];
#endif

void enableUsartReceiveBuffer(bool enable);

#ifdef UNIT_TEST
extern int clearUsartReceiveBufferCallCount;
#endif
void clearUsartReceiveBuffer(void);

#define LCD_PORT_READ 1
#define LCD_PORT_WRITE 0

#ifdef UNIT_TEST
extern int lcdPortRw;
#endif

void setLcdPortRw(int rw);

#ifdef UNIT_TEST
extern int portAIdx;
extern int portAState[];
#endif

void setPortA(int data);

#ifdef UNIT_TEST
extern int pulseLcdCeCallCount;
#endif

void pulseLcdCe(void);

typedef unsigned char BYTE;

typedef union {
    struct {
        unsigned RCIF                   :1;
    };
} PIR1bits_t;

extern PIR1bits_t PIR1bits;

typedef union {
    struct {
        unsigned OERR                   :1;
        unsigned CREN                   :1;
    };
} RCSTAbits_t;

extern RCSTAbits_t RCSTAbits;

typedef struct {
    unsigned TMR3IF: 1;
} PIR2bits_t;

extern PIR2bits_t PIR2bits;

typedef struct {
    unsigned TMR3IE: 1;
} PIE2bits_t;

extern PIE2bits_t PIE2bits;

extern BYTE PORTA;
extern BYTE TMR3H;
extern BYTE TMR3L;

typedef struct {
    unsigned RB0: 1;
    unsigned RB1: 1;
    unsigned RB2: 1;
    unsigned RB3: 1;
} PORTBbits_t;

extern PORTBbits_t PORTBbits;

typedef struct {
} RingBuffer;

extern RingBuffer ringBufferForReceive;
extern RingBuffer ringBufferForLcd;

int getCharFromRingBuffer(RingBuffer *p);

extern int usartPort;
int USART_RECEIVE_CHAR(void);

extern int ringBufferData;
void PUT_CHAR_TO_RING_BUFFER(RingBuffer *p, int c);

#ifdef __cplusplus
}
#endif

#endif
