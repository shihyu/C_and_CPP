#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FileAccessorContext {
    FILE *fp;
    const char * const pFname;
    const char * const pMode;
    bool (* const processor)(struct FileAccessorContext *pThis);
} FileAccessorContext;

bool access_file(FileAccessorContext *pThis);
FILE *get_file_pointer(FileAccessorContext *pThis);

#define NEW_FILE(pFname, pMode, processor) {NULL, (pFname), (pMode), (processor)}

#ifdef __cplusplus
}
#endif

#endif
