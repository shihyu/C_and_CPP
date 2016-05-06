//7FALSE.C
//试位法求方程根
#include  "math.h"
int false(a, b, eps, f, x)     //执行试位法
double a, b, eps, (*f)(double), *x;
{
    int m;
    double fa, fb, y;
    m = 0;
    fa = (*f)(a);
    fb = (*f)(b);

    if (fa * fb > 0) {
        return (-1);
    }

    do {
        m = m + 1;
        *x = (a * fb - b * fa) / (fb - fa);
        y = (*f)(*x);

        if (y * fa < 0) {
            b = *x;
            fb = y;
        } else  {
            a = *x;
            fa = y;
        }
    } while (fabs(y) >= eps);

    return (m);
}


