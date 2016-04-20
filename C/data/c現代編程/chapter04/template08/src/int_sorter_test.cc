#include "gtest/gtest.h"

#include <stdio.h>
#include <stdbool.h>
#include "int_sorter.h"

static bool write_int(FILE *fp, int i) {
    return fwrite(&i, sizeof(int), 1, fp) == 1;
}

static int read_int(FILE *fp) {
    int ret;
    fread(&ret, sizeof(int), 1, fp);
    return ret;
}

TEST(TemplateTest, normalCase) {
    char tmpFileName[L_tmpnam+1];
    tmpnam(tmpFileName);

    FILE *fp = fopen(tmpFileName, "wb");
    EXPECT_EQ(true, write_int(fp, 1231));
    EXPECT_EQ(true, write_int(fp, 1));
    EXPECT_EQ(true, write_int(fp, 441));
    EXPECT_EQ(0, fclose(fp));

    int_sorter(tmpFileName);

    fp = fopen(tmpFileName, "rb");
    EXPECT_EQ(1, read_int(fp));
    EXPECT_EQ(441, read_int(fp));
    EXPECT_EQ(1231, read_int(fp));
    EXPECT_EQ(0, fclose(fp));
}

TEST(TemplateTest, emptyFile) {
    char tmpFileName[L_tmpnam+1];
    tmpnam(tmpFileName);

    FILE *fp = fopen(tmpFileName, "w");
    EXPECT_EQ(0, fclose(fp));
    
    int_sorter(tmpFileName);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

