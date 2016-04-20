#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FileReaderContext {
    const char * const pFname;
    void (* const processor)(struct FileReaderContext *pThis, FILE *fp);
} FileReaderContext;

int read_file(FileReaderContext *pFileCtx);

#ifdef __cplusplus
}
#endif

#endif
