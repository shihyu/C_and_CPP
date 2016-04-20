#include <stdbool.h>
#include "stack.h"

static bool isStackFull(const Stack *p) {
    return p->top == p->size;
}

static bool isStackEmpty(const Stack *p) {
    return p->top == 0;
}

bool validateRange(Validator *p, int val) {
    RangeValidator *pThis = (RangeValidator *)p;
    return pThis->min <= val && val <= pThis->max;
}

bool validatePrevious(Validator *p, int val) {
    PreviousValueValidator *pThis = (PreviousValueValidator *)p;
    if (val < pThis->previousValue) return false;
    pThis->previousValue = val;
    return true;
}

bool validate(Validator *p, int val) {
    if (! p) return true;
    return p->validate(p, val);
}

// true: 成功, false: 失敗
bool push(Stack *p, int val) {
    if (! validate(p->pValidator, val) || isStackFull(p)) return false;
    p->pBuf[p->top++] = val;
    return true;
}

// true: 成功, false: 失敗
bool pop(Stack *p, int *pRet) {
    if (isStackEmpty(p)) return false;
    *pRet = p->pBuf[--p->top];
    return true;
}

bool validateChain(Validator *p, int val) {
    ChainedValidator *pThis = (ChainedValidator *)p;

    p = pThis->pWrapped;
    if (! p->validate(p, val)) return false;

    p = pThis->pNext;
    return !p || p->validate(p, val);
}
