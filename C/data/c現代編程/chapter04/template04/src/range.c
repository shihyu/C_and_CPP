#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_reader.h"

static int range_processor(FILE *fp) {
    int min = INT_MAX;
    int max = INT_MIN;
    char buf[256];

    while ((fgets(buf, sizeof(buf), fp)) != NULL) {
        if (buf[0] == '\n') return -1; // 空行を発見したら-1を返す。
        int value = atoi(buf);
        min = min > value ? value : min;
        max = max < value ? value : max;
    }

    return max - min;
}

int range(const char *pFname) {
    return read_file(pFname, range_processor);
}
