#include "stdio.h"
#include "simp2.c"
main()
{
    int i, n, m, itmax;
    int  sf();
    double f();
    double d, alf, eps, a[2], b[2], xopt[3], fx[4], x[4 * 2];
    n = 2;
    m = 2;
    xopt[0] = 1.0;
    xopt[1] = 0.0;
    a[0] = 0.0;
    a[1] = 0.0;
    b[0] = 20.0;
    b[1] = 20.0;
    eps = 1.0e-30;
    alf = 1.3;
    d = 10.0;
    itmax = 200;
    i = simp2(n, m, a, b, d, alf, eps, x, fx, xopt, sf, f,
              itmax); /* 调用有约束的单纯形法*/
    printf("iterations times =%d\n", i);
    printf("\n");

    for (i = 0; i <= 3; i++)
        printf("x(0)=%e  x(1)=%e  f=%e\n",
               x[i * n + 0], x[i * n + 1], fx[i]);

    printf("\n");

    for (i = 0; i <= 1; i++) {
        printf("xopt(%d)=%e ", i, xopt[i]);
    }

    printf("fopt=%e\n", xopt[2]);
    printf("\n");
}

#include "math.h"
double f(x)
double* x;
{
    double y;
    y = -(9.0 - (x[0] - 2.0) * (x[0] - 4.0));
    y = y * x[1] * x[1] * x[1];
    return (y);
}

#include "math.h"
int sf(x)
double* x;
{
    double c[2], w[2], d[2];
    c[0] = 0.0;
    c[1] = 0.0;
    d[0] = x[0] / 2.0;
    d[1] = 6.0;
    w[0] = x[1];
    w[1] = x[0] + x[1] * 2.0;

    if (c[0] <= w[0] && w[0] <= d[0])
        if (c[1] <= w[1] && w[1] <= d[1]) {
            return (1);
        }

    return (0);
}

