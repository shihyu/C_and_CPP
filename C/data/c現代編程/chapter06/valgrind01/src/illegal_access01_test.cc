#include <memory.h>

#include "gtest/gtest.h"
#include "illegal_access01.h"

TEST(IllegalReadTest01, illegalRead01) {
    int *p = (int *)malloc(10);
    illegalRead(p);
    free(p);
}

TEST(IllegalReadTest01, illegalRead02) {
    int buf[10];
    illegalRead(buf);
}

int globalBuf[10];

TEST(IllegalReadTest01, illegalRead03) {
    illegalRead(globalBuf);
}

TEST(IllegalWriteTest01, illegalWrite01) {
    int *p = (int *)malloc(10);
    illegalWrite(p);
    free(p);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
