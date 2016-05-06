
#include "stdio.h"
#include "9ffts.c"
main()
{
    double a, b, eps, t, fftsf(double);
    a = 0.0;
    b = 1.0;
    eps = 0.000001;
    t = ffts(a, b, eps, fftsf);
    printf("\n");
    printf("t=%13.5e\n", t);
    printf("\n");
}

#include "math.h"
double fftsf(x)
double x;
{
    double y;
    y = exp(-x * x);
    return (y);
}

