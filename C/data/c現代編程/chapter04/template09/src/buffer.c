#include <stdlib.h>
#include <assert.h>

#include "buffer.h"

bool buffer(BufferContext *pThis) {
    assert(pThis);
    bool ret = pThis->processor(pThis);
    free(pThis->pBuf);
    return ret;
}

void *allocate_buffer(BufferContext *pThis, size_t size) {
    assert(pThis);
    assert(pThis->pBuf == NULL);
    pThis->pBuf = malloc(size);
    pThis->size = size;
    return pThis->pBuf;
}
