#include <stdio.h>
#include "validator.h"

static void rangeView(ValidatorVisitor *pThis, RangeValidator *p);
static void previousValueView(ValidatorVisitor *pThis, PreviousValueValidator *p);

typedef struct ViewVisitor {
    ValidatorVisitor base;
    char *pBuf;
    size_t size;
} ViewVisitor;

void printValidator(Validator *p, char *pBuf, size_t size) {
    ViewVisitor visitor = {{rangeView, previousValueView}, pBuf, size};
    p->accept(p, &visitor.base);
}

static void rangeView(ValidatorVisitor *pThis, RangeValidator *p) {
    ViewVisitor *pVisitor = (ViewVisitor* )pThis;
    snprintf(pVisitor->pBuf, pVisitor->size, "Range(%d-%d)", p->min, p->max);
}

static void previousValueView(ValidatorVisitor *pThis, PreviousValueValidator *p) {
    ViewVisitor *pVisitor = (ViewVisitor* )pThis;
    snprintf(pVisitor->pBuf, pVisitor->size, "Previous");
}
