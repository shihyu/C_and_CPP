
#include "math.h"
double ffts(a, b, eps, f)
double a, b, eps, (*f)();
{
    int n, k;
    double fa, fb, h, t1, p, s, x, t;
    fa = (*f)(a);
    fb = (*f)(b);
    n = 1;
    h = b - a;
    t1 = h * (fa + fb) / 2.0;
    p = eps + 1.0;

    while (p >= eps) {
        s = 0.0;

        for (k = 0; k <= n - 1; k++) {
            x = a + (k + 0.5) * h;
            s = s + (*f)(x);
        }

        t = (t1 + h * s) / 2.0;
        p = fabs(t1 - t);
        t1 = t;
        n = n + n;
        h = h / 2.0;
    }

    return (t);
}

