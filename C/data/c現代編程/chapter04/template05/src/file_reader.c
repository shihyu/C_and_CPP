#include "file_reader.h"

int read_file(FileReaderContext *pCtx) {
    FILE *fp = fopen(pCtx->pFname, "r");
    if (fp == NULL) return -1;

    pCtx->processor(pCtx, fp);

    fclose(fp);
    return 0;
}
