#include <stdbool.h>
#include <stdio.h>
#include "validator.h"

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

void viewRange(Validator *p, char *pBuf, size_t size) {
    RangeValidator *pThis = (RangeValidator *)p;
    snprintf(pBuf, size, "Range(%d-%d)", pThis->min, pThis->max);
}

void viewPrevious(Validator *pThis, char *pBuf, size_t size) {
    snprintf(pBuf, size, "Previous");
}


