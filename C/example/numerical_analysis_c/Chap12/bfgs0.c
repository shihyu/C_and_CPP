#include "stdio.h"
#include "math.h"
#include "bfgs.c"
#include "bsl1.c"

void main()
{
    double  eps, fopt, x[3], xm[3], g[3];
    int itmax = 50, n = 3, it;
    double f();
    void df();
    eps = 1e-7;
    x[0] = x[1] = x[2] = 0.0;
    it = bfgs(x, xm, n, &fopt, f, df, eps, itmax);
    printf("iterations = %d:\nx0=%f,x1=%f,x2=%f\nfopt=%f\n", it, xm[0], xm[1],
           xm[2], fopt);
    df(xm, g, 3);
    printf("df[0]=%f, df[1]=%f, df[2]=%f\n", g[0], g[1], g[2]);
}
double f(x, n)
double* x;
int n;
{
    double y;

    if (n != 3) {
        return (0.0);
    }

    y = (x[0] - 1.0) * (x[0] - 1.0) + (x[1] - 2.0) * (x[1] - 2.0) + (x[2] - 3.0) *
        (x[2] - 3.0);
    return bsl1(0, y);
}
void df(x, g, n)
double* x, *g;
int n;
{
    double y;

    if (n != 3) {
        return;
    }

    y = (x[0] - 1.0) * (x[0] - 1.0) + (x[1] - 2.0) * (x[1] - 2.0) + (x[2] - 3.0) *
        (x[2] - 3.0);
    g[0] = -bsl1(1, y) * (2 * (x[0] - 1.0));
    g[1] = -bsl1(1, y) * (2 * (x[1] - 2.0));
    g[2] = -bsl1(1, y) * (2 * (x[2] - 3.0));
}