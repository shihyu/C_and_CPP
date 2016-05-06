
#include "math.h"
#include "stdio.h"
#include "14gam1.c"
double beta(a, b, x)
double a, b, x;
{
    double y;
    double bt(double, double, double);

    if (a <= 0.0) {
        printf("err**a<=0!");
        return (-1.0);
    }

    if (b <= 0.0) {
        printf("err**b<=0!");
        return (-1.0);
    }

    if ((x < 0.0) || (x > 1.0)) {
        printf("err**x<0 or x>1 !");
        return (1.0e+70);
    }

    if ((x == 0.0) || (x == 1.0)) {
        y = 0.0;
    } else {
        y = a * log(x) + b * log(1.0 - x);
        y = exp(y);
        y = y * gam1(a + b) / (gam1(a) * gam1(b));
    }

    if (x < (a + 1.0) / (a + b + 2.0)) {
        y = y * bt(a, b, x) / a;
    } else {
        y = 1.0 - y * bt(b, a, 1.0 - x) / b;
    }

    return (y);
}

static double bt(a, b, x)
double a, b, x;
{
    int k;
    double d, p0, q0, p1, q1, s0, s1;
    p0 = 0.0;
    q0 = 1.0;
    p1 = 1.0;
    q1 = 1.0;

    for (k = 1; k <= 100; k++) {
        d = (a + k) * (a + b + k) * x;
        d = -d / ((a + k + k) * (a + k + k + 1.0));
        p0 = p1 + d * p0;
        q0 = q1 + d * q0;
        s0 = p0 / q0;
        d = k * (b - k) * x;
        d = d / ((a + k + k - 1.0) * (a + k + k));
        p1 = p0 + d * p1;
        q1 = q0 + d * q1;
        s1 = p1 / q1;

        if (fabs(s1 - s0) < fabs(s1) * 1.0e-07) {
            return (s1);
        }
    }

    printf("a or b too big !");
    return (s1);
}

