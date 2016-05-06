
#include "math.h"
#include "stdio.h"
#include "9fpqg.c"
main()
{
    double a, b, eps, s, fpqgf(double);
    a = 0.0;
    b = 4.3;
    eps = 0.000001;
    s = fpqg(a, b, eps, fpqgf);
    printf("\n");
    printf("s=%13.5e\n", s);
    printf("\n");
}

double fpqgf(x)
double x;
{
    double y;
    y = exp(-x * x);
    return (y);
}

