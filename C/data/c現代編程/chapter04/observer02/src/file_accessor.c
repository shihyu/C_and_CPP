#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "file_accessor.h"
#include "array_list.h"

static void fire_error(FileAccessorContext *pThis);

bool access_file(FileAccessorContext *pThis) {
    assert(pThis);
    bool ret = pThis->processor(pThis);
    if (pThis->fp != NULL) {
        if (fclose(pThis->fp) != 0) {
            fire_error(pThis);
            ret = false;
        }
    }

    return ret;
}

FILE *get_file_pointer(FileAccessorContext *pThis) {
    assert(pThis);
    if (pThis->fp == NULL) {
        pThis->fp = fopen(pThis->pFname, pThis->pMode);
        if (pThis->fp == NULL) 
            fire_error(pThis);
    }

    return pThis->fp;
}

long file_size(FileAccessorContext *pFileCtx) {
    long save = file_current_pos(pFileCtx);
    if (save < 0) return -1;

    if (set_file_pos(pFileCtx, 0, SEEK_END) != 0) return -1;
    
    long size = file_current_pos(pFileCtx);
    set_file_pos(pFileCtx, save, SEEK_SET);

    return size;
}

long file_current_pos(FileAccessorContext *pThis) {
    assert(pThis);
    FILE *fp = get_file_pointer(pThis);
    if (fp == NULL) return -1;

    long ret = ftell(fp);
    if (ret < 0) fire_error(pThis);
    return ret;
}

int set_file_pos(FileAccessorContext *pThis, long offset, int whence) {
    assert(pThis);
    FILE *fp = get_file_pointer(pThis);
    if (fp == NULL) return -1;

    int ret = fseek(fp, offset, whence);
    if (ret != 0) fire_error(pThis);
    return ret;
}

bool read_file(FileAccessorContext *pThis, BufferContext *pBufCtx) {
    FILE *fp = get_file_pointer(pThis);
    if (fp == NULL) return false;

    if (pBufCtx->size != fread(pBufCtx->pBuf, 1, pBufCtx->size, fp)) {
        fire_error(pThis);
        return false;
    }
    return true;
}

bool write_file(FileAccessorContext *pThis, BufferContext *pBufCtx) {
    FILE *fp = get_file_pointer(pThis);
    if (fp == NULL) return false;

    if (pBufCtx->size != fwrite(pBufCtx->pBuf, 1, pBufCtx->size, fp)) {
        fire_error(pThis);
        return false;
    }
    return true;
}

void add_file_error_observer(FileAccessorContext *pThis, FileErrorObserver *pErrorObserver) {
    ArrayList *pTable = &pThis->observer_table;
    pTable->add(pTable, pErrorObserver);
}

void remove_file_error_observer(FileAccessorContext *pThis, FileErrorObserver *pErrorObserver) {
    ArrayList *pTable = &pThis->observer_table;
    pTable->remove(pTable, pErrorObserver);
}

static void fire_error(FileAccessorContext *pThis) {
    ArrayList *pTbl = &pThis->observer_table;
    int i;
    for (i = 0; i < pTbl->index; ++i) {
        FileErrorObserver *pObserver = pTbl->get(pTbl, i);
        pObserver->onError(pObserver, pThis);
    }
}

