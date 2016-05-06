
#include "math.h"
void cdiv(a, b, c, d, u, v)
double a, b, c, d, *u, *v;
{
    double p, q, s, w;
    p = a * c;
    q = -b * d;
    s = (a + b) * (c - d);
    w = c * c + d * d;

    if (w + 1.0 == 1.0) {
        *u = 1.0e+35 * a / fabs(a);
        *v = 1.0e+35 * b / fabs(b);
    } else {
        *u = (p - q) / w;
        *v = (s - p - q) / w;
    }

    return;
}

