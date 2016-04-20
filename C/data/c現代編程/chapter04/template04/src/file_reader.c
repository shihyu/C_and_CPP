#include "file_reader.h"

int read_file(const char *pFname, int (*processor)(FILE *fp)) {
    FILE *fp = fopen(pFname, "r");
    if (fp == NULL) return -1;

    int ret = processor(fp);

    fclose(fp);
    return ret;
}
