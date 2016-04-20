#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FileAccessorContext {
    const char * const pFname;
    const char * const pMode;
    void (* const processor)(struct FileAccessorContext *pThis, FILE *fp);
} FileAccessorContext;

bool access_file(FileAccessorContext *pFileCtx);

#ifdef __cplusplus
}
#endif

#endif
