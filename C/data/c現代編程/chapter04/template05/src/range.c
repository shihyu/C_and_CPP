#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_reader.h"

typedef struct {
    FileReaderContext base;
    int result;
} MyFileReaderContext;

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

static void calc_range(FileReaderContext *p, FILE *fp) {
    MyFileReaderContext *pCtx = (MyFileReaderContext *)p;
    pCtx->result = range_processor(fp);
}

int range(const char *pFname) {
    MyFileReaderContext ctx = {{pFname, calc_range}, 0};

    if (read_file(&ctx.base) != 0) {
        fprintf(stderr, "Cannot open file '%s'.\n", pFname);
    }
    return ctx.result;
}
