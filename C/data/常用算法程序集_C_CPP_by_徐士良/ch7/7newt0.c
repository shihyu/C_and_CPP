
#include "math.h"
#include "stdio.h"
#include "7newt.c"
main()
{
    int js, k;
    double x, eps;
    void newtf(double, double []);
    eps = 0.000001;
    js = 60;
    x = 1.5;
    k = newt(&x, eps, js, newtf);

    if (k >= 0) {
        printf("k=%d  x=%13.6e\n", k, x);
    }

    printf("\n");
}

void newtf(x, y)
double x, y[2];
{
    y[0] = x * x * (x - 1.0) - 1.0;
    y[1] = 3.0 * x * x - 2.0 * x;
    return;
}

