
#include "math.h"
int atkn(x, eps, js, f)
int js;
double eps, *x, (*f)();
{
    int flag, l;
    double u, v, x0;
    l = 0;
    x0 = *x;
    flag = 0;

    while ((flag == 0) && (l != js)) {
        l = l + 1;
        u = (*f)(x0);
        v = (*f)(u);

        if (fabs(u - v) < eps) {
            x0 = v;
            flag = 1;
        } else {
            x0 = v - (v - u) * (v - u) / (v - 2.0 * u + x0);
        }
    }

    *x = x0;
    l = js - l;
    return (l);
}

