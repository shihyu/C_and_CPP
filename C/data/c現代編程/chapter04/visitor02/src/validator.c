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

void acceptRange(Validator *p, ValidatorVisitor *pVisitor) {
    pVisitor->visitRange(pVisitor, (RangeValidator *)p);
}

void acceptPrevious(Validator *p, ValidatorVisitor *pVisitor) {
    pVisitor->visitPreviousValue(pVisitor, (PreviousValueValidator *)p);
}


