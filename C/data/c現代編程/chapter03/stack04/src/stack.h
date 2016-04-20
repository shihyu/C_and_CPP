#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int top;
    const size_t size;
    int * const pBuf;

    const bool needRangeCheck;
    const int min;
    const int max;
} Stack;

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#define newStack(buf) {                    \
    0, sizeof(buf) / sizeof(int), (buf),   \
    false, 0, 0                            \
} 

#define newStackWithRangeCheck(buf, min, max) { \
    0, sizeof(buf) / sizeof(int), (buf),        \
    true, min, max                              \
}

#ifdef __cplusplus
}
#endif

#endif
