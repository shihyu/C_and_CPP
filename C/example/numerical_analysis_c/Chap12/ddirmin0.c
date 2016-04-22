#include "stdio.h"
#include "math.h"
#include "ddirmin.c"

void main()
{
    double  eps, fopt, x[3], p[3], xmin[3];
    int itmax = 50, n = 3;
    double f();
    void df();
    eps = 1e-7;
    x[0] = x[1] = x[2] = 0.0;
    p[0] = p[1] = p[2] = 0.2;

    fopt = ddirmin(x, p, xmin, n, f, df, eps, itmax);
    printf("%f,%f,%f,%f\n", xmin[0], xmin[1], xmin[2], fopt);
}

double f(x, n)
double* x;
int n;
{
    if (n != 3) {
        return (0.0);
    }

    return (x[0] - 1.0) * (x[0] - 1.0) + (x[1] - 1.0) * (x[1] - 1.0) +
           (x[2] - 1.0) * (x[2] - 1.0);
}

void df(x, g, n)
double* x, *g;
int n;
{
    if (n != 3) {
        return;
    }

    g[0] = 2 * (x[0] - 1.0);
    g[1] = 2 * (x[1] - 1.0);
    g[2] = 2 * (x[2] - 1.0);
}
