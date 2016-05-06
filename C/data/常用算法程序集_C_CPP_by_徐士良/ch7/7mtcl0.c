
#include "math.h"
#include "stdio.h"
#include "7mtcl.c"
main()
{
    int m;
    double x, b, eps, mtclf(double);
    x = 0.5;
    b = 1.0;
    m = 10;
    eps = 0.00001;
    mtcl(&x, b, m, eps, mtclf);
    printf("\n");
    printf("x=%13.6e\n", x);
    printf("\n");
}

double mtclf(x)
double x;
{
    double y;
    y = exp(-x * x * x) - sin(x) / cos(x) + 800.0;
    return (y);
}

