
#include "stdlib.h"
#include "math.h"
int snse(n, eps, x, js, ff)
int n, js;
double eps, x[], (*ff)();
{
    int l, j;
    double f, d, s, *y;
    y = malloc(n * sizeof(double));
    l = js;
    f = (*ff)(x, y, n);

    while (f >= eps) {
        l = l - 1;

        if (l == 0) {
            free(y);
            return (js);
        }

        d = 0.0;

        for (j = 0; j <= n - 1; j++) {
            d = d + y[j] * y[j];
        }

        if (d + 1.0 == 1.0) {
            free(y);
            return (-1);
        }

        s = f / d;

        for (j = 0; j <= n - 1; j++) {
            x[j] = x[j] - s * y[j];
        }

        f = (*ff)(x, y, n);
    }

    free(y);
    return (js - l);
}

