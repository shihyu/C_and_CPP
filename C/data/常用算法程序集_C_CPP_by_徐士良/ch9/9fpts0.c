
#include "stdio.h"
#include "9fpts.c"
main()
{
    double a, b, eps, t, d, fptsf(double);
    a = -1.0;
    b = 1.0;
    eps = 0.000001;
    d = 0.0001;
    t = fpts(a, b, eps, d, fptsf);
    printf("\n");
    printf("t=%13.5e\n", t);
    printf("\n");
}

double fptsf(x)
double x;
{
    double y;
    y = 1.0 / (1.0 + 25.0 * x * x);
    return (y);
}

