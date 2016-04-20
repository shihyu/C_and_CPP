#include "gtest/gtest.h"

#include <stdio.h>

#include "array_list.h"

TEST(ArrayListTest, add_test) {
    void *table[2];
    ArrayList buf = new_array_list(table);

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)0, buf.size(&buf));
    ASSERT_EQ(table, buf.pBuf);

    char str1[] = "Hello";
    buf.add(&buf, str1);

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)1, buf.size(&buf));
    ASSERT_EQ(table, buf.pBuf);

    char str2[] = "World";
    buf.add(&buf, str2);

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)2, buf.size(&buf));
    ASSERT_EQ(table, buf.pBuf);

    char str3[] = "Overflow";
    ASSERT_DEATH(buf.add(&buf, str3), ".*Assertion .* failed.");
}

TEST(ArrayListTest, remove_test) {
    void *table[2];
    ArrayList buf = new_array_list(table);

    char str1[] = "Hello";
    buf.add(&buf, str1);

    char str2[] = "World";
    buf.add(&buf, str2);

    ASSERT_EQ(str1, buf.remove(&buf, str1));

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)1, buf.size(&buf));
    ASSERT_EQ(str2, buf.get(&buf, 0));

    ASSERT_EQ(NULL, buf.remove(&buf, str1));

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)1, buf.size(&buf));
    ASSERT_EQ(str2, buf.get(&buf, 0));

    ASSERT_EQ(str2, buf.remove(&buf, str2));

    ASSERT_EQ(2, buf.capacity);
    ASSERT_EQ((size_t)0, buf.size(&buf));

    ASSERT_EQ(NULL, buf.remove(&buf, str2));
}

TEST(ArrayListTest, get_test) {
    void *table[2];
    ArrayList buf = new_array_list(table);

    ASSERT_DEATH(buf.get(&buf, -1), ".*Assertion .* failed.");
    ASSERT_DEATH(buf.get(&buf, 0), ".*Assertion .* failed.");

    char str1[] = "Hello";
    buf.add(&buf, str1);

    ASSERT_EQ(str1, buf.get(&buf, 0));
    ASSERT_DEATH(buf.get(&buf, 1), ".*Assertion .* failed.");
}
