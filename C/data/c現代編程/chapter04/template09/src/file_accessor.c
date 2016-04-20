#include <assert.h>

#include "file_accessor.h"

bool access_file(FileAccessorContext *pThis) {
    assert(pThis);
    bool ret = pThis->processor(pThis);
    if (pThis->fp != NULL) {
        if (fclose(pThis->fp) != 0) ret = false;
    }
    return ret;
}

FILE *get_file_pointer(FileAccessorContext *pThis) {
    assert(pThis);
    if (pThis->fp == NULL)
        pThis->fp = fopen(pThis->pFname, pThis->pMode);

    return pThis->fp;
}

