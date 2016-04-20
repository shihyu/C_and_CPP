#include "gtest/gtest.h"
#include "uninitialized01.h"

TEST(UninitializedTest01, uninitialized01) {
    uninitialized();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
