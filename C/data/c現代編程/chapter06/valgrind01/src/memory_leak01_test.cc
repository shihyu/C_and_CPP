#include "gtest/gtest.h"
#include "memory_leak01.h"

TEST(MemoryLeakTest01, memoryLeak01) {
    memoryLeak();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
