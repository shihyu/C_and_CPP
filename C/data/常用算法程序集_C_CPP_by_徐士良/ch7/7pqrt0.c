
#include "math.h"
#include "stdio.h"
#include "7pqrt.c"
main()
{
    double x, eps, pqrtf(double);
    int k;
    x = 1.0;
    eps = 0.000001;
    k = pqrt(&x, eps, pqrtf);
    printf("\n");
    printf("k=%d   x=%13.6e\n", k, x);
    printf("\n");
}

double pqrtf(x)
double x;
{
    double y;
    y = x * x * (x - 1.0) - 1.0;
    return (y);
}

