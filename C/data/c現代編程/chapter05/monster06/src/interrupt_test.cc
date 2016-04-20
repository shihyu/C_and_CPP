#include <stdbool.h>

#include "gtest/gtest.h"

#include "hw.h"
#include "interrupt.h"

extern "C" {

int onUsartInterruptCallCount;
static void onUsartInterruptMock(void) {
    ++onUsartInterruptCallCount;
}

int onTimer3InterruptCallCount;
static void onTimer3InterruptMock(void) {
    ++onTimer3InterruptCallCount;
}

}

TEST(LowPriorityISRCode, usartInterrupt) {
    PIR1bits.RCIF = 1u;
    pOnTimer3Interrupt = onTimer3InterruptMock;
    pOnUsartInterrupt = onUsartInterruptMock;

    onUsartInterruptCallCount = 0;
    onTimer3InterruptCallCount = 0;

    lowPriorityISRCode();

    EXPECT_EQ(1, onUsartInterruptCallCount);
    EXPECT_EQ(0, onTimer3InterruptCallCount);
}

TEST(LowPriorityISRCode, timer3Interrupt) {
    PIR1bits.RCIF = 0u;
    PIR2bits.TMR3IF = 1;

    pOnTimer3Interrupt = onTimer3InterruptMock;
    pOnUsartInterrupt = onUsartInterruptMock;

    onUsartInterruptCallCount = 0;
    onTimer3InterruptCallCount = 0;

    lowPriorityISRCode();

    EXPECT_EQ(0, onUsartInterruptCallCount);
    EXPECT_EQ(1, onTimer3InterruptCallCount);
}

TEST(LowPriorityISRCode, noInterrupt) {
    PIR1bits.RCIF = 0u;
    PIR2bits.TMR3IF = 0;

    pOnTimer3Interrupt = onTimer3InterruptMock;
    pOnUsartInterrupt = onUsartInterruptMock;

    onUsartInterruptCallCount = 0;
    onTimer3InterruptCallCount = 0;

    lowPriorityISRCode();

    EXPECT_EQ(0, onUsartInterruptCallCount);
    EXPECT_EQ(0, onTimer3InterruptCallCount);
}

extern "C" {

int resetUsartPortCallCount;
void resetUsartPortMock(void) {
    ++resetUsartPortCallCount;
}

}

TEST(OnUsartInterrupt, onOverrun) {
    pOnUsartInterrupt = MOCKABLE(onUsartInterrupt);
    RCSTAbits.OERR = 1;
    pResetUsartPort = resetUsartPortMock;
    resetUsartPortCallCount = 0;

    onUsartInterrupt();
    EXPECT_EQ(1, resetUsartPortCallCount);
}

TEST(OnUsartInterrupt, normal) {
    pOnUsartInterrupt = MOCKABLE(onUsartInterrupt);
    RCSTAbits.OERR = 0;
    usartPort = 12;
    pResetUsartPort = resetUsartPortMock;
    resetUsartPortCallCount = 0;

    onUsartInterrupt();
    EXPECT_EQ(0, resetUsartPortCallCount);
    EXPECT_EQ(12, ringBufferData);
}

extern "C" {

int processLcdDataCallCount;
int processLcdDataMockArg;
void processLcdDataMock(int c) {
    processLcdDataMockArg = c;
    ++processLcdDataCallCount;
}

}

TEST(OnTimer3Interrupt, normal) {
    pOnTimer3Interrupt = MOCKABLE(onTimer3Interrupt);
    pProcessLcdData = processLcdDataMock;
    processLcdDataCallCount = 0;
    ringBufferData = 23;
    PIE2bits.TMR3IE = 1;

    onTimer3Interrupt();
    EXPECT_EQ(1, processLcdDataCallCount);
    EXPECT_EQ(23, processLcdDataMockArg);
    EXPECT_EQ(1u, PIE2bits.TMR3IE);
}

TEST(OnTimer3Interrupt, eof) {
    pOnTimer3Interrupt = MOCKABLE(onTimer3Interrupt);
    pProcessLcdData = processLcdDataMock;
    processLcdDataCallCount = 0;
    ringBufferData = -1;
    PIE2bits.TMR3IE = 1;

    onTimer3Interrupt();
    EXPECT_EQ(0, processLcdDataCallCount);
    EXPECT_EQ(0u, PIE2bits.TMR3IE);
}

extern "C" {

int performLcdControlCallCount;
void performLcdControlMock(void) {
    ++performLcdControlCallCount;
}

int performLcdDataMockArg;
int performLcdDataCallCount;
void performLcdDataMock(int c) {
    performLcdDataMockArg = c;
    ++performLcdDataCallCount;
}

}

TEST(ProcessLcdData, escape) {
    pProcessLcdData = MOCKABLE(processLcdData);
    pPerformLcdControl = performLcdControlMock;
    pPerformLcdData = performLcdDataMock;
    performLcdDataCallCount = 0;
    performLcdControlCallCount = 0;

    processLcdData(0xFE);

    EXPECT_EQ(1, performLcdControlCallCount);
    EXPECT_EQ(0, performLcdDataCallCount);
}

TEST(ProcessLcdData, normal) {
    pProcessLcdData = MOCKABLE(processLcdData);
    performLcdControlCallCount = 0;
    performLcdDataCallCount = 0;
    performLcdDataMockArg = 0;
    pPerformLcdControl = performLcdControlMock;
    pPerformLcdData = performLcdDataMock;

    processLcdData(12);

    EXPECT_EQ(0, performLcdControlCallCount);
    EXPECT_EQ(1, performLcdDataCallCount);
    EXPECT_EQ(12, performLcdDataMockArg);
}

TEST(ResetUsartPort, normalCase) {
    pResetUsartPort = MOCKABLE(resetUsartPort);
    usartReceiveBufferEnabledIdx = 0;
    clearUsartReceiveBufferCallCount = 0;

    resetUsartPort();
    
    EXPECT_EQ(1, clearUsartReceiveBufferCallCount);
    EXPECT_EQ(2, usartReceiveBufferEnabledIdx);
    EXPECT_EQ(false, usartReceiveBufferEnabled[0]);
    EXPECT_EQ(true, usartReceiveBufferEnabled[1]);
}

TEST(Write1ByteToLcd, normalCase) {
    lcdPortRw = LCD_PORT_READ;
    portAIdx = 0;
    pulseLcdCeCallCount = 0;

    write1byteToLcd(0x5a);
    EXPECT_EQ(LCD_PORT_WRITE, lcdPortRw);
    EXPECT_EQ(2, portAIdx);
    EXPECT_EQ(5, portAState[0]);
    EXPECT_EQ(0xA, portAState[1]);
    EXPECT_EQ(2, pulseLcdCeCallCount);
}

TEST(Write1ByteToLcd, normalCase2) {
    lcdPortRw = LCD_PORT_READ;
    portAIdx = 0;
    pulseLcdCeCallCount = 0;

    write1byteToLcd(0xa5);
    EXPECT_EQ(LCD_PORT_WRITE, lcdPortRw);
    EXPECT_EQ(2, portAIdx);
    EXPECT_EQ(0xA, portAState[0]);
    EXPECT_EQ(5, portAState[1]);
    EXPECT_EQ(2, pulseLcdCeCallCount);
}

extern "C" {

int write1byteToLcdMockArg;
int write1byteToLcdCallCount;
void write1byteToLcdMock(int c) {
    write1byteToLcdMockArg = c;
    ++write1byteToLcdCallCount;
}

}

TEST(PerformLcdControl, normal) {
    pPerformLcdControl = MOCKABLE(performLcdControl);
    write1byteToLcdCallCount = 0;
    write1byteToLcdMockArg = 0;
    ringBufferData = 12;
    PORTBbits.RB0 = LCD_MODE_DATA;
    pWrite1byteToLcd = write1byteToLcdMock;
    PIR2bits.TMR3IF = 1;
    TMR3H = 0;
    TMR3L = 0;

    performLcdControl();

    EXPECT_EQ(LCD_MODE_CONTROL, PORTBbits.RB0);
    EXPECT_EQ(1, write1byteToLcdCallCount);
    EXPECT_EQ(12, write1byteToLcdMockArg);
    EXPECT_EQ(0u, PIR2bits.TMR3IF);
    EXPECT_EQ(65467u >> 8, TMR3H);
    EXPECT_EQ(65467u & 0xff, TMR3L);
}

TEST(PerformLcdData, normal) {
    pPerformLcdData = MOCKABLE(performLcdData);
    write1byteToLcdCallCount = 0;
    write1byteToLcdMockArg = 0;
    PORTBbits.RB0 = LCD_MODE_CONTROL;
    pWrite1byteToLcd = write1byteToLcdMock;
    PIR2bits.TMR3IF = 1;
    TMR3H = 0;
    TMR3L = 0;

    performLcdData(23);

    EXPECT_EQ(LCD_MODE_DATA, PORTBbits.RB0);
    EXPECT_EQ(1, write1byteToLcdCallCount);
    EXPECT_EQ(23, write1byteToLcdMockArg);
    EXPECT_EQ(0u, PIR2bits.TMR3IF);
    EXPECT_EQ(65467u >> 8, TMR3H);
    EXPECT_EQ(65467u & 0xff, TMR3L);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
