#include "gtest/gtest.h"

#include <stdbool.h>
#include "stack.h"

typedef struct TestValidator {
    Validator base;
    bool result;
} TestValidator;

extern "C" {
    static bool validateTest(Validator *p, int val) {
        TestValidator *pThis = (TestValidator *)p;
        return pThis->result;
    }
}

static TestValidator trueValidator = {{validateTest}, true};
static TestValidator falseValidator = {{validateTest}, false};

TEST(StackTest, popFromEmptyStackReturnsFalse) {
    int buf[16];
    Stack stack = newStack(buf);
    EXPECT_EQ(false, pop(&stack, 0));
}

TEST(StackTest, popReturnsStackTopAndRemoveIt) {
    int buf[16];
    Stack stack = newStack(buf);

    EXPECT_EQ(true, push(&stack, 123));

    int ret;
    EXPECT_EQ(true, pop(&stack, &ret));
    EXPECT_EQ(123, ret);

    EXPECT_EQ(false, pop(&stack, &ret));
}

TEST(StackTest, pushToFullStackReturnsFalse) {
    int buf[16];
    Stack stack = newStack(buf);

    for (int i = 0; i < 16; ++i) push(&stack, i);
    EXPECT_EQ(false, push(&stack, 100));

    int ret;
    EXPECT_EQ(true, pop(&stack, &ret));
    EXPECT_EQ(15, ret);
}

TEST(StackTest, pushWithRangeCheck) {
    int buf[16];
    RangeValidator validator = newRangeValidator(0, 9);
    Stack stack = newStackWithValidator(buf, &validator.base);
    EXPECT_EQ(false, push(&stack, -1));
    EXPECT_EQ(false, push(&stack, 10));
}

TEST(StackTest, pushWithPreviousCheck) {
    int buf[16];
    PreviousValueValidator validator = newPreviousValueValidator;
    Stack stack = newStackWithValidator(buf, &validator.base);
    EXPECT_EQ(true, push(&stack, 3));
    EXPECT_EQ(false, push(&stack, 2));
}

TEST(StackTest, singleChaindValidator) {
    ChainedValidator trueChainedValidator = newChainedValidator(&trueValidator.base, NULL);
    EXPECT_EQ(true, trueChainedValidator.base.validate(&trueChainedValidator.base, 0));

    ChainedValidator falseChainedValidator = newChainedValidator(&falseValidator.base, NULL);
    EXPECT_EQ(false, falseChainedValidator.base.validate(&falseChainedValidator.base, 0));
}

TEST(StackTest, falseTrueChainedValidator) {
    ChainedValidator falseChain = newChainedValidator(&falseValidator.base, NULL);
    ChainedValidator trueFalseChain = newChainedValidator(&trueValidator.base, &falseChain.base);

    EXPECT_EQ(false, trueFalseChain.base.validate(&trueFalseChain.base, 0));
}

TEST(StackTest, trueFalseChainedValidator) {
    ChainedValidator trueChain = newChainedValidator(&trueValidator.base, NULL);
    ChainedValidator falseTrueChain = newChainedValidator(&falseValidator.base, &trueChain.base);

    EXPECT_EQ(false, falseTrueChain.base.validate(&falseTrueChain.base, 0));
}

TEST(StackTest, trueTrueChainedValidator) {
    ChainedValidator trueChain = newChainedValidator(&trueValidator.base, NULL);
    ChainedValidator trueTrueChain = newChainedValidator(&trueValidator.base, &trueChain.base);

    EXPECT_EQ(true, trueTrueChain.base.validate(&trueTrueChain.base, 0));
}

TEST(StackTest, falseFalseChainedValidator) {
    ChainedValidator falseChain = newChainedValidator(&falseValidator.base, NULL);
    ChainedValidator falseFalseChain = newChainedValidator(&falseValidator.base, &falseChain.base);

    EXPECT_EQ(false, falseFalseChain.base.validate(&falseFalseChain.base, 0));
}

TEST(StackTest, rangePrevChainedValidator) {
    RangeValidator rangeValidator = newRangeValidator(0, 9);
    PreviousValueValidator prevValidator = newPreviousValueValidator;

    ChainedValidator prevChain = newChainedValidator(&prevValidator.base, NULL);
    ChainedValidator rangeChain = newChainedValidator(&rangeValidator.base, &prevChain.base);

    int buf[16];
    Stack stack = newStackWithValidator(buf, &rangeChain.base);
    ASSERT_EQ(false, push(&stack, -1));
    ASSERT_EQ(true, push(&stack, 5));
    ASSERT_EQ(false, push(&stack, 4));
    ASSERT_EQ(true, push(&stack, 9));
    ASSERT_EQ(false, push(&stack, 10));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
