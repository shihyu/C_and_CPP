
#include "math.h"
double simp(a, b, eps, f)
double a, b, eps, (*f)();
{
    int n, k;
    double h, t1, t2, s1, s2, ep, p, x;
    n = 1;
    h = b - a;
    t1 = h * ((*f)(a) + (*f)(b)) / 2.0;
    s1 = t1;
    ep = eps + 1.0;

    while (ep >= eps) {
        p = 0.0;

        for (k = 0; k <= n - 1; k++) {
            x = a + (k + 0.5) * h;
            p = p + (*f)(x);
        }

        t2 = (t1 + h * p) / 2.0;
        s2 = (4.0 * t2 - t1) / 3.0;
        ep = fabs(s2 - s1);
        t1 = t2;
        s1 = s2;
        n = n + n;
        h = h / 2.0;
    }

    return (s2);
}

