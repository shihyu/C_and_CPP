#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static bool reader(FileAccessorContext *pFileCtx);
static bool do_with_buffer(BufferContext *pBufCtx);
static bool writer(FileAccessorContext *pFileCtx);
static int comparator(const void *p1, const void *p2);
static void file_error(FileErrorObserver *pThis, FileAccessorContext *pFileCtx);

typedef struct {
    BufferContext base;
    Context *pAppCtx;
} MyBufferContext;

typedef struct {
    FileAccessorContext base;
    MyBufferContext *pBufCtx;
} MyFileAccessorContext;

typedef struct {
    FileAccessorContext base;
    long size;
} SizeGetterContext;

static FileErrorObserver file_error_observer = {
    file_error
};

IntSorterError int_sorter(const char *pFname) {
    Context ctx = {pFname, ERR_CAT_OK};

    MyBufferContext bufCtx = {{NULL, 0, do_with_buffer}, &ctx};
    buffer(&bufCtx.base);
    return ctx.errorCategory;
}

static bool do_with_buffer(BufferContext *p) {
    MyBufferContext *pBufCtx = (MyBufferContext *)p;
    MyFileAccessorContext readFileCtx = {
        {NULL, pBufCtx->pAppCtx->pFname, "rb", reader, &file_error_observer},
        pBufCtx
    };

    if (! access_file(&readFileCtx.base)) return false;

    qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

    MyFileAccessorContext writeFileCtx = {
        {NULL, pBufCtx->pAppCtx->pFname, "wb", writer, &file_error_observer},
        pBufCtx
    };
    return access_file(&writeFileCtx.base);
}

static bool reader(FileAccessorContext *p) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;

    long size = file_size(p);
    if (size == -1) return false;

    if (! allocate_buffer(&pFileCtx->pBufCtx->base, size)) {
        pFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_CAT_MEMORY;
        return false;
    }

    return read_file(p, &pFileCtx->pBufCtx->base);
}

static bool writer(FileAccessorContext *p) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
    return write_file(p, &pFileCtx->pBufCtx->base);
}

static int comparator(const void *p1, const void *p2) {
    int i1 = *(const int *)p1;
    int i2 = *(const int *)p2;
    if (i1 < i2) return -1;
    if (i1 > i2) return 1;
    return 0;
}

static void file_error(FileErrorObserver *pThis, FileAccessorContext *pFileCtx) {
    default_file_error_observer.onError(pThis, pFileCtx);

    MyFileAccessorContext *pMyFileCtx = (MyFileAccessorContext *)pFileCtx;
    pMyFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_CAT_FILE;
}
