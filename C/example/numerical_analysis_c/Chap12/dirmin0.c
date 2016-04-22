#include "stdio.h"
#include "math.h"
#include "dirmin.c"

void main()
{
    double  eps, fopt, x[3], p[3], xmin[3], t;
    int i, itmax = 50, n = 3;
    double f();
    eps = 1e-7;
    x[0] = x[1] = x[2] = 0.0;
    t = sqrt(2);
    printf("dirmin:\n");
    printf("    x0       x1      x2       fmin\n");

    for (i = 0; i < 10; i++) {
        p[0] = t * cos(3.1415926 * i / 36);
        p[1] = t * sin(3.1415926 * i / 36);
        p[2] = 1.0;

        fopt = dirmin(x, p, xmin, n, f, eps, itmax);
        printf("%7.6f %7.6f %7.6f %7.6f\n", xmin[0], xmin[1], xmin[2], fopt);
    }
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
