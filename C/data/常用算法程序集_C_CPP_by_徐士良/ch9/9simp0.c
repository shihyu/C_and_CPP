
#include "stdio.h"
#include "9simp.c"
main()
{
    double a, b, eps, t, simpf(double);
    a = 0.0;
    b = 1.0;
    eps = 0.000001;
    t = simp(a, b, eps, simpf);
    printf("\n");
    printf("t=%13.5e\n", t);
    printf("\n");
}

#include "math.h"
double simpf(x)
double x;
{
    double y;
    y = log(1.0 + x) / (1.0 + x * x);
    return (y);
}

