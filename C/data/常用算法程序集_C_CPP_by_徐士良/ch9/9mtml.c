
#include "stdlib.h"
#include "math.h"
#include "3rnd1.c"
double mtml(n, a, b, f)
int n;
double a[], b[], (*f)();
{
    int m, i;
    double r, s, d, *x;
    x = malloc(n * sizeof(double));
    r = 1.0;
    d = 10000.0;
    s = 0.0;

    for (m = 0; m <= 9999; m++) {
        for (i = 0; i <= n - 1; i++) {
            x[i] = a[i] + (b[i] - a[i]) * rnd1(&r);
        }

        s = s + (*f)(n, x) / d;
    }

    for (i = 0; i <= n - 1; i++) {
        s = s * (b[i] - a[i]);
    }

    free(x);
    return (s);
}

