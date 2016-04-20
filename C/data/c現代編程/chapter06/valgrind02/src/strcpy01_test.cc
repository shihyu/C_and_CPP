#include <string.h>

#include "gtest/gtest.h"
#include "strcpy01.h"

TEST(StrCpy01, strcpy01) {
    char p[] = "Hello";
    char *pResult = dropTop(p);
    EXPECT_EQ(0, strcmp(pResult, "ello"));
}
