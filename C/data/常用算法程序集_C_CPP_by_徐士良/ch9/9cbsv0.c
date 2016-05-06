
#include "math.h"
#include "stdio.h"
#include "9cbsv.c"
main()
{
    double a, b, eps, s, cbsvf(double);
    a = 2.5;
    b = 8.4;
    eps = 0.000001;
    s = cbsv(a, b, eps, cbsvf);
    printf("\n");
    printf("s=%13.5e\n", s);
    printf("\n");
}

double cbsvf(x)
double x;
{
    double y;
    y = x * x + sin(x);
    return (y);
}

