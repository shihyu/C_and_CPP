#include <stdbool.h>

#include "gtest/gtest.h"

extern "C" {
#include "hw.h"
}

namespace unit_test {

#include "interrupt.h"
#include "interrupt.c"

TEST(ResetUsartPort, normalCase) {
    usartReceiveBufferEnabledIdx = 0;
    clearUsartReceiveBufferCallCount = 0;

    resetUsartPort();
    
    EXPECT_EQ(1, clearUsartReceiveBufferCallCount);
    EXPECT_EQ(2, usartReceiveBufferEnabledIdx);
    EXPECT_EQ(false, usartReceiveBufferEnabled[0]);
    EXPECT_EQ(true, usartReceiveBufferEnabled[1]);
}

TEST(Write1ByteToLcd, normalCase) {
    PORTBbits.RB2 = LCD_PORT_READ;
    portAIdx = 0;
    pulseLcdCeCallCount = 0;

    write1byteToLcd(0x5a);
    EXPECT_EQ(LCD_PORT_WRITE, PORTBbits.RB2);
    EXPECT_EQ(2, portAIdx);
    EXPECT_EQ(5, portAState[0]);
    EXPECT_EQ(0xA, portAState[1]);
    EXPECT_EQ(2, pulseLcdCeCallCount);
}

TEST(Write1ByteToLcd, normalCase2) {
    PORTBbits.RB2 = LCD_PORT_READ;
    portAIdx = 0;
    pulseLcdCeCallCount = 0;

    write1byteToLcd(0xa5);
    EXPECT_EQ(LCD_PORT_WRITE, PORTBbits.RB2);
    EXPECT_EQ(2, portAIdx);
    EXPECT_EQ(0xA, portAState[0]);
    EXPECT_EQ(5, portAState[1]);
    EXPECT_EQ(2, pulseLcdCeCallCount);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
