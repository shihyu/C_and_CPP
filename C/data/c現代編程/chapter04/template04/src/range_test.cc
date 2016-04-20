#include "gtest/gtest.h"

#include <stdio.h>
#include "range.h"

TEST(TemplateTest, normalCase) {
    char tmpFileName[L_tmpnam+1];
    tmpnam(tmpFileName);

    FILE *fp = fopen(tmpFileName, "w");
    fputs("1231\n", fp);
    fputs("1\n", fp);
    fputs("441\n", fp);
    EXPECT_EQ(0, fclose(fp));
    
    EXPECT_EQ(1230, range(tmpFileName));
}

TEST(TemplateTest, emptyFile) {
    char tmpFileName[L_tmpnam+1];
    tmpnam(tmpFileName);

    FILE *fp = fopen(tmpFileName, "w");
    EXPECT_EQ(0, fclose(fp));
    
    EXPECT_EQ(1, range(tmpFileName));
}

TEST(TemplateTest, blankLine) {
    char tmpFileName[L_tmpnam+1];
    tmpnam(tmpFileName);

    FILE *fp = fopen(tmpFileName, "w");
    fputs("1231\n", fp);
    fputs("\n", fp);
    fputs("22\n", fp);
    EXPECT_EQ(0, fclose(fp));

    EXPECT_EQ(-1, range(tmpFileName));

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

