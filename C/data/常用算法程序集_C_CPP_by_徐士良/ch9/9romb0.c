
#include "stdio.h"
#include "9romb.c"
main()
{
    double a, b, eps, t, rombf(double);
    a = 0.0;
    b = 1.0;
    eps = 0.000001;
    t = romb(a, b, eps, rombf);
    printf("\n");
    printf("t=%13.5e\n", t);
    printf("\n");
}

double rombf(x)
double x;
{
    double y;
    y = x / (4.0 + x * x);
    return (y);
}

