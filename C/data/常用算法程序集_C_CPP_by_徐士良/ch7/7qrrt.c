
#include "stdlib.h"
#include "5hhqr.c"
int qrrt(a, n, xr, xi, eps, jt)
int n, jt;
double a[], xr[], xi[], eps;
{
    int i, j;
    double* q;
    q = malloc(n * n * sizeof(double));

    for (j = 0; j <= n - 1; j++) {
        q[j] = -a[n - j - 1] / a[n];
    }

    for (j = n; j <= n * n - 1; j++) {
        q[j] = 0.0;
    }

    for (i = 0; i <= n - 2; i++) {
        q[(i + 1)*n + i] = 1.0;
    }

    i = hhqr(q, n, xr, xi, eps, jt);
    free(q);
    return (i);
}

