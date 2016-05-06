
#include "math.h"
#include "3rnd1.c"
void mtcl(x, b, m, eps, f)
int m;
double* x, b, eps, (*f)();
{
    int k;
    double xx, a, r, y, x1, y1;
    a = b;
    k = 1;
    r = 1.0;
    xx = *x;
    y = (*f)(xx);

    while (a >= eps) {
        x1 = rnd1(&r);
        x1 = -a + 2.0 * a * x1;
        x1 = xx + x1;
        y1 = (*f)(x1);
        k = k + 1;

        if (fabs(y1) >= fabs(y)) {
            if (k > m) {
                k = 1;
                a = a / 2.0;
            }
        } else {
            k = 1;
            xx = x1;
            y = y1;

            if (fabs(y) < eps) {
                *x = xx;
                return;
            }
        }
    }

    *x = xx;
    return;
}

