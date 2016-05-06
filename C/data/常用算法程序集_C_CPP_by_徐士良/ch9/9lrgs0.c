
#include "math.h"
#include "stdio.h"
#include "9lrgs.c"
main()
{
    double a, b, eps, g, lrgsf(double);
    a = 2.5;
    b = 8.4;
    eps = 0.000001;
    g = lrgs(a, b, eps, lrgsf);
    printf("\n");
    printf("g=%13.5e\n", g);
    printf("\n");
}

double lrgsf(x)
double x;
{
    double y;
    y = x * x + sin(x);
    return (y);
}

