#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffer.h"

bool buffer(BufferContext *pThis) {
    bool ret = pThis->processor(pThis);
    free(pThis->pBuf);
    return ret;
}

void *allocate_buffer(BufferContext *pBufCtx, size_t size) {
    assert(pBufCtx->pBuf == NULL);
    pBufCtx->pBuf = malloc(size);
    pBufCtx->size = size;
    return pBufCtx->pBuf;
}
