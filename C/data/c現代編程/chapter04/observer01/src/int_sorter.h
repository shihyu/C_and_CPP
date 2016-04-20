#ifndef _INT_SORTER_H_
#define _INT_SORTER_H_

#include "buffer.h"
#include "file_accessor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ERR_CAT_OK = 0,
    ERR_CAT_FILE,
    ERR_CAT_MEMORY
} IntSorterError;

typedef struct {
    const char *pFname;
    FileAccessorContext *pFileCtx;
    BufferContext *pBufCtx;
    int errorCategory;
} Context;

IntSorterError int_sorter(const char *pFname);

#ifdef __cplusplus
}
#endif

#endif
