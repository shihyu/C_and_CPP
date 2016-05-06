
#include "math.h"
double fpts(a, b, eps, d, f)
double a, b, eps, d, (*f)();
{
    double h, t[2], f0, f1, t0, z;
    void ppp();
    h = b - a;
    t[0] = 0.0;
    f0 = (*f)(a);
    f1 = (*f)(b);
    t0 = h * (f0 + f1) / 2.0;
    ppp(a, b, h, f0, f1, t0, eps, d, t, f);
    z = t[0];
    return (z);
}

static void ppp(x0, x1, h, f0, f1, t0, eps, d, t, ff)
double x0, x1, h, f0, f1, t0, eps, d, t[], (*ff)();
{
    double x, f, t1, t2, p, g, eps1;
    x = x0 + h / 2.0;
    f = (*ff)(x);
    t1 = h * (f0 + f) / 4.0;
    t2 = h * (f + f1) / 4.0;
    p = fabs(t0 - (t1 + t2));

    if ((p < eps) || (h / 2.0 < d)) {
        t[0] = t[0] + (t1 + t2);
        return;
    } else {
        g = h / 2.0;
        eps1 = eps / 1.4;
        ppp(x0, x, g, f0, f, t1, eps1, d, t, ff);
        ppp(x, x1, g, f, f1, t2, eps1, d, t, ff);
        return;
    }
}

