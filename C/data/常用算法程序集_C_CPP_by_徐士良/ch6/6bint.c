
#include "4trmul.c"
#include "6gaus.c"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
int bint(a, n, b, eps, x)
int n;
double a[], b[], x[], eps;
{
    int i, j, k, kk;
    double* p, *r, *e, q, qq;
    int gaus(double [], double [], int);
    void trmul(double [], double [], int, int, int, double []);
    p = malloc(n * n * sizeof(double));
    r = malloc(n * sizeof(double));
    e = malloc(n * sizeof(double));
    i = 60;

    for (k = 0; k <= n - 1; k++)
        for (j = 0; j <= n - 1; j++) {
            p[k * n + j] = a[k * n + j];
        }

    for (k = 0; k <= n - 1; k++) {
        x[k] = b[k];
    }

    kk = gaus(p, x, n);

    if (kk == 0) {
        free(p);
        free(r);
        free(e);
        return (kk);
    }

    q = 1.0 + eps;

    while (q >= eps) {
        if (i == 0) {
            free(p);
            free(r);
            free(e);
            return (i);
        }

        i = i - 1;
        trmul(a, x, n, n, 1, e);

        for (k = 0; k <= n - 1; k++) {
            r[k] = b[k] - e[k];
        }

        for (k = 0; k <= n - 1; k++)
            for (j = 0; j <= n - 1; j++) {
                p[k * n + j] = a[k * n + j];
            }

        kk = gaus(p, r, n);

        if (kk == 0) {
            free(p);
            free(r);
            free(e);
            return (kk);
        }

        q = 0.0;

        for (k = 0; k <= n - 1; k++) {
            qq = fabs(r[k]) / (1.0 + fabs(x[k] + r[k]));

            if (qq > q) {
                q = qq;
            }
        }

        for (k = 0; k <= n - 1; k++) {
            x[k] = x[k] + r[k];
        }
    }

    free(p);
    free(r);
    free(e);
    return (1);
}

