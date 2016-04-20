#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static bool reader(FileAccessorContext *pThis);
static long file_size(FileAccessorContext *pThis);
static bool do_with_buffer(BufferContext *p);
static bool writer(FileAccessorContext *pThis);
static int comparator(const void *p1, const void *p2);
static void file_error(Context *pCtx);
static long file_current_pos(FileAccessorContext *pFileCtx);
static int set_file_pos(FileAccessorContext *pFileCtx, long offset, int whence);

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

IntSorterError int_sorter(const char *pFname) {
    Context ctx = {pFname, ERR_CAT_OK};

    MyBufferContext bufCtx = {{NULL, 0, do_with_buffer}, &ctx};
    buffer(&bufCtx.base);
    return ctx.errorCategory;
}

static bool do_with_buffer(BufferContext *p) {
    MyBufferContext *pBufCtx = (MyBufferContext *)p;
    MyFileAccessorContext readFileCtx = {{NULL, pBufCtx->pAppCtx->pFname, "rb", reader}, pBufCtx};

    if (! access_file(&readFileCtx.base)) {
        file_error(pBufCtx->pAppCtx);
        return false;
    }

    qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

    MyFileAccessorContext writeFileCtx = {{NULL, pBufCtx->pAppCtx->pFname, "wb", writer}, pBufCtx};
    if (! access_file(&writeFileCtx.base)) {
        file_error(pBufCtx->pAppCtx);
        return false;
    }

    return true;
}

static bool reader(FileAccessorContext *p) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
    MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

    long size = file_size(p);
    if (size == -1) {
        file_error(pBufCtx->pAppCtx);
        return false;
    }

    if (! allocate_buffer(&pBufCtx->base, size)) {
        pBufCtx->pAppCtx->errorCategory = ERR_CAT_MEMORY;
        return false;
    }

    FILE *fp = get_file_pointer(p);
    if (pBufCtx->base.size != fread(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp)) {
        file_error(pBufCtx->pAppCtx);
        return false;
    }

    return true;
}

static bool writer(FileAccessorContext *p) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
    MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

    FILE *fp = get_file_pointer(p);
    if (fwrite(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp) != pBufCtx->base.size) {
        file_error(pBufCtx->pAppCtx);
        return false;
    }

    return true;
}

static int comparator(const void *p1, const void *p2) {
    int i1 = *(const int *)p1;
    int i2 = *(const int *)p2;
    if (i1 < i2) return -1;
    if (i1 > i2) return 1;
    return 0;
}

static void file_error(Context *pCtx) {
    fprintf(stderr, "%s: %s\n", pCtx->pFname, strerror(errno));
    pCtx->errorCategory = ERR_CAT_FILE;
}

static long file_size(FileAccessorContext *pThis) {
    long save = file_current_pos(pThis);
    if (save < 0) return -1;

    if (set_file_pos(pThis, 0, SEEK_END) != 0) return -1;

    long size = file_current_pos(pThis);
    if (set_file_pos(pThis, save, SEEK_SET) != 0) return -1;

    return size;
}

static long file_current_pos(FileAccessorContext *pFileCtx) {
    assert(pFileCtx);
    FILE *fp = get_file_pointer(pFileCtx);
    if (fp == NULL) return -1;

    return ftell(fp);
}

static int set_file_pos(FileAccessorContext *pFileCtx, long offset, int whence) {
    assert(pFileCtx);
    FILE *fp = get_file_pointer(pFileCtx);
    if (fp == NULL) return -1;

    return fseek(fp, offset, whence);
}
