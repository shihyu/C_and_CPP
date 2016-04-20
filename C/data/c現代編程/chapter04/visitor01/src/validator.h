#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Validator {
    bool (* const validate)(struct _Validator *pThis, int val);
    void (* const view)(struct _Validator *pThis, char *pBuf, size_t size);
} Validator;

typedef struct {
    Validator base;
    const int min;
    const int max;
} RangeValidator;

typedef struct {
    Validator base;
    int previousValue;
} PreviousValueValidator;

void viewRange(Validator *pThis, char *pBuf, size_t size);
void viewPrevious(Validator *pThis, char *pBuf, size_t size);

bool validateRange(Validator *pThis, int val);
bool validatePrevious(Validator *pThis, int val);

#define newRangeValidator(min, max) \
    {{validateRange, viewRange}, (min), (max)}

#define newPreviousValueValidator \
    {{validatePrevious, viewPrevious}, 0}

#ifdef __cplusplus
}
#endif

#endif
