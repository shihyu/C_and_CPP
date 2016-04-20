#include <stdbool.h>
#include "stack.h"

static bool isStackFull(const Stack *p) {
    return p->top == p->size;
}

static bool isStackEmpty(const Stack *p) {
    return p->top == 0;
}

static bool isRangeOk(const Stack *p, int val) {
    return ! p->needRangeCheck ||
        (p->min <= val && val <= p->max);
}

// true: 成功, false: 失敗
bool push(Stack *p, int val) {
    if (! isRangeOk(p, val) || isStackFull(p)) return false;
    p->pBuf[p->top++] = val;
    return true;
}

// true: 成功, false: 失敗
bool pop(Stack *p, int *pRet) {
    if (isStackEmpty(p)) return false;
    *pRet = p->pBuf[--p->top];
    return true;
}
