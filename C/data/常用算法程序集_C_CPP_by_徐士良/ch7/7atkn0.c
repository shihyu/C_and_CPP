
#include "math.h"
#include "stdio.h"
#include "7atkn.c"
main()
{
    int js, k;
    double x, eps, atknf(double);
    eps = 0.0000001;
    js = 20;
    x = 0.0;
    k = atkn(&x, eps, js, atknf);
    printf("\n");
    printf("k=%d  x=%13.6e\n", k, x);
    printf("\n");
}

double atknf(x)
double x;
{
    double y;
    y = 6.0 - x * x;
    return (y);
}

