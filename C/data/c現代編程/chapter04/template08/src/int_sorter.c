#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static void reader(FileAccessorContext *pThis, FILE *fp);
static long file_size(const char *pFname);
static void size_reader(FileAccessorContext *pThis, FILE *fp);
static void do_with_buffer(BufferContext *p);
static void writer(FileAccessorContext *pThis, FILE *fp);
static int comparator(const void *p1, const void *p2);
static void file_error(Context *pCtx);

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

    long size = file_size(pFname);
    if (size == -1) {
        file_error(&ctx);
        return ctx.errorCategory;
    }

    MyBufferContext bufCtx = {{NULL, size, do_with_buffer}, &ctx};
    if (! buffer(&bufCtx.base)) {
        ctx.errorCategory = ERR_CAT_MEMORY;
    }

    return ctx.errorCategory;
}

static void do_with_buffer(BufferContext *p) {
    MyBufferContext *pBufCtx = (MyBufferContext *)p;
    MyFileAccessorContext readFileCtx = {{pBufCtx->pAppCtx->pFname, "rb", reader}, pBufCtx};

    if (! access_file(&readFileCtx.base)) {
        file_error(pBufCtx->pAppCtx);
        return;
    }

    qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

    MyFileAccessorContext writeFileCtx = {{pBufCtx->pAppCtx->pFname, "wb", writer}, pBufCtx};
    if (! access_file(&writeFileCtx.base)) {
        file_error(pBufCtx->pAppCtx);
        return;
    }
}

static void reader(FileAccessorContext *p, FILE *fp) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
    MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

    if (pBufCtx->base.size != fread(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp)) {
        file_error(pBufCtx->pAppCtx);
    }
}

static void writer(FileAccessorContext *p, FILE *fp) {
    MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
    MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

    if (fwrite(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp) != pBufCtx->base.size) {
        file_error(pBufCtx->pAppCtx);
    }
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

static long file_size(const char *pFname) {
    SizeGetterContext ctx = {{pFname, "rb", size_reader}, 0};

    if (! access_file(&ctx.base)) {
        return -1;
    }

    return ctx.size;
}

static void size_reader(FileAccessorContext *p, FILE *fp) {
    SizeGetterContext *pThis = (SizeGetterContext *)p;
    pThis->size = -1;

    if (fseek(fp, 0, SEEK_END) == 0)
        pThis->size = ftell(fp);
}
