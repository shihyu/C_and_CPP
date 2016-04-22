#include "math.h"
#include "stdio.h"
#include "simp1.c"
main()
{
    int i;
    double  simf();
    double d, u, v, eps, x[3], xx[6], f[3];
    d = 2.0;
    u = 1.5;
    v = 0.5;
    eps = 1.0e-30;
    x[0] = 0.0;
    x[1] = 0.0;

    i = simp1(d, 2, v, 1.0, u, xx, f, x, simf, eps, 200);

    printf("iterations times: i=%3d\n", i);
    printf("\n");
    printf("the last simplex points:\n");

    for (i = 0; i <= 2; i++)
        printf("x(0)=%e  x(1)=%e  f=%e\n",
               xx[i * 2 + 0], xx[i * 2 + 1], f[i]);

    printf("\n");
    printf("optimization Points:\n");
    printf("x(0)=%e  x(1)=%e  minf=%e\n", x[0], x[1], x[2]);
}

double simf(x, n)
double* x;
{
    double y;

    if (n != 2) {
        return (0.0);
    }

    y = x[1] - x[0] * x[0];
    y = 10.0 * y * y;
    y = y + (2.0 - x[0]) * (3.0 - x[0]);
    return (y);
}

