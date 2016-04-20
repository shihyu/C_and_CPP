#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#ifdef UNIT_TEST
    #define MOCKABLE(method) mockable##method
#else
    #define MOCKABLE(method) method
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_ESCAPE_CHAR (BYTE)0xFE

void lowPriorityISRCode(void);
void processLcdData(int c);
void disableTime3Interrupt(void);
void resetUsartPort(void);
void write1byteToLcd(int c);
void performLcdControl(void);
void performLcdData(int c);

unsigned int isUsartInterruptOccurred(void);
void onUsartInterrupt(void);
int isTimer3Overflow(void);
void onTimer3Interrupt(void);
int upper4bitOf(int c);
int lower4bitOf(int c);

#define LCD_MODE_CONTROL 0u
#define LCD_MODE_DATA 1u

#ifdef UNIT_TEST
void MOCKABLE(resetUsartPort)(void);
extern void (*pResetUsartPort)(void);

void MOCKABLE(write1byteToLcd)(int c);
extern void (*pWrite1byteToLcd)(int c);

void MOCKABLE(performLcdControl)(void);
extern void (*pPerformLcdControl)(void);

void MOCKABLE(performLcdData)(int c);
extern void (*pPerformLcdData)(int c);

void MOCKABLE(processLcdData)(int c);
extern void (*pProcessLcdData)(int c);

void MOCKABLE(onUsartInterrupt)(void);
extern void (*pOnUsartInterrupt)(void);

void MOCKABLE(onTimer3Interrupt)(void);
extern void (*pOnTimer3Interrupt)(void);
#endif

#define LCD_DATA_EOF -1

#ifdef __cplusplus
}
#endif

#endif
