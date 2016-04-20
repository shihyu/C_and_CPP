#include "gtest/gtest.h"

extern "C" {
#include "hw.h"
}

namespace unit_test {

#include "interrupt.h"
#include "interrupt.c"

static unsigned int usartOverrunOccurred;
static unsigned int mockIsUsartOverrunOccurred(LowPriorityInterrupt *pThis) {
    return usartOverrunOccurred;
}

static int onUsartInterruptCallCount;
static void mockOnUsartInterrupt(LowPriorityInterrupt *pThis) {
    ++onUsartInterruptCallCount;
}

static int timer3Overflow;
static int mockIsTimer3Overflow(LowPriorityInterrupt *pThis) {
    return timer3Overflow;
}

static int onTimer3InterruptCallCount;
static void mockOnTimer3Interrupt(LowPriorityInterrupt *pThis) {
    ++onTimer3InterruptCallCount;
}

TEST(InterruptTest, usartInterrupt) {
    LowPriorityInterrupt interrupt = {
        mockIsUsartOverrunOccurred,
        mockOnUsartInterrupt,
        mockIsTimer3Overflow,
        mockOnTimer3Interrupt
    };

    usartOverrunOccurred = 1;
    onUsartInterruptCallCount = 0;

    performLowPriorityInterrupt(&interrupt);
    EXPECT_EQ(1, onUsartInterruptCallCount);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
