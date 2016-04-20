#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ValidatorVisitor;

typedef struct Validator {
    bool (* const validate)(struct Validator *pThis, int val);
    void (* const accept)(struct Validator *pThis, struct ValidatorVisitor *pVisitor);
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

typedef struct ValidatorVisitor {
    void (* const visitRange)(struct ValidatorVisitor *pThis, RangeValidator *p);
    void (* const visitPreviousValue)(struct ValidatorVisitor *pThis, PreviousValueValidator *p);
} ValidatorVisitor;

void acceptRange(Validator *pThis, ValidatorVisitor *pVisitor);
void acceptPrevious(Validator *pThis, ValidatorVisitor *pVisitor);

bool validateRange(Validator *pThis, int val);
bool validatePrevious(Validator *pThis, int val);

#define newRangeValidator(min, max) \
    {{validateRange, acceptRange}, (min), (max)}

#define newPreviousValueValidator \
    {{validatePrevious, acceptPrevious}, 0}

#ifdef __cplusplus
}
#endif

#endif
