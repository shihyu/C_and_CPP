#include "gtest/gtest.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "validator.h"

TEST(ValidatorTest, rangeValidator) {
    RangeValidator v = newRangeValidator(0, 9);
    char buf[32];
    v.base.view(&v.base, buf, sizeof(buf));

    EXPECT_EQ(0, strcmp("Range(0-9)", buf));
}

TEST(ValidatorTest, previousValidator) {
    PreviousValueValidator v = newPreviousValueValidator;
    char buf[32];
    v.base.view(&v.base, buf, sizeof(buf));

    EXPECT_EQ(0, strcmp("Previous", buf));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
