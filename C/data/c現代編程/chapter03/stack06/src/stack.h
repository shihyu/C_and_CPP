#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Validator {
    bool (* const validate)(struct _Validator *pThis, int val);
    void * const pData;
} Validator;

typedef struct {
    const int min;
    const int max;
} Range;

typedef struct {
    int previousValue;
} PreviousValue;

typedef struct {
    int top;
    const size_t size;
    int * const pBuf;
    Validator * const pValidator;
} Stack;

bool validateRange(Validator *pThis, int val);
bool validatePrevious(Validator *pThis, int val);

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#define newStack(buf) {                  \
    0, sizeof(buf) / sizeof(int), (buf), \
    NULL                                 \
} 

#define rangeValidator(pRange) { \
    validateRange,               \
    pRange                       \
}

#define previousValidator(pPrevious) { \
    validatePrevious,                  \
    pPrevious                          \
}

#define newStackWithValidator(buf, pValidator) { \
    0, sizeof(buf) / sizeof(int), (buf),         \
    pValidator                                   \
}

#ifdef __cplusplus
}
#endif

#endif
