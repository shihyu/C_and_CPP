
#include "math.h"
#include "stdio.h"
#include "9pqg2.c"
main()
{
    double a, b, eps, s, pqg2f(double, double);
    void  pqg2s(double, double []);
    a = 0.0;
    b = 1.0;
    eps = 0.00005;
    s = pqg2(a, b, eps, pqg2s, pqg2f);
    printf("\n");
    printf("s=%13.5e\n", s);
    printf("\n");
}

void pqg2s(x, y)
double x, y[2];
{
    y[1] = sqrt(1.0 - x * x);
    y[0] = -y[1];
    return;
}

double pqg2f(x, y)
double x, y;
{
    double z;
    z = exp(x * x + y * y);
    return (z);
}

