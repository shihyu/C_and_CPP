
#include "math.h"
#include "3rnd1.c"
double mtcl(a, b, f)
double a, b, (*f)();
{
    int m;
    double r, d, x, s;
    r = 1.0;
    s = 0.0;
    d = 10000.0;

    for (m = 0; m <= 9999; m++) {
        x = a + (b - a) * rnd1(&r);
        s = s + (*f)(x) / d;
    }

    s = s * (b - a);
    return (s);
}

