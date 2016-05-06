
#include "math.h"
#include "stdio.h"
#include "9sim2.c"
main()
{
    double a, b, eps, s, sim2f(double, double);
    void  sim2s(double, double []);
    a = 0.0;
    b = 1.0;
    eps = 0.0001;
    s = sim2(a, b, eps, sim2s, sim2f);
    printf("\n");
    printf("s=%13.5e\n", s);
    printf("\n");
}

void sim2s(x, y)
double x, y[2];
{
    y[0] = -sqrt(1.0 - x * x);
    y[1] = -y[0];
    return;
}

double sim2f(x, y)
double x, y;
{
    double z;
    z = exp(x * x + y * y);
    return (z);
}

