
#include "stdio.h"
#include "9hmgs.c"
main()
{
    double hmgsf(double);
    printf("\n");
    printf("g=%13.5e\n", hmgs(hmgsf));
    printf("\n");
}

double hmgsf(x)
double x;
{
    double y;
    y = x * x * exp(-x * x);
    return (y);
}

