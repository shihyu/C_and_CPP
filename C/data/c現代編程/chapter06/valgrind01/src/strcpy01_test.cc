#include <string.h>

#include "gtest/gtest.h"
#include "strcpy01.h"

TEST(StrCpy01, strcpy01) {
    char p[] = "Hello";
    char *pResult = dropTop(p);
    EXPECT_EQ(0, strcmp(pResult, "ello"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
