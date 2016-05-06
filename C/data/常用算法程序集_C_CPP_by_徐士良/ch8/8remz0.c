
#include "math.h"
#include "stdio.h"
#include "8remz.c"
main()
{
    int i;
    double a, b, eps, p[5];
    double remzf(double);
    a = -1.0;
    b = 1.0;
    eps = 1.0e-10;
    remz(a, b, p, 4, eps, remzf);
    printf("\n");

    for (i = 0; i <= 3; i++) {
        printf("p(%2d)=%13.5e\n", i, p[i]);
    }

    printf("\n");
    printf("MAX(p-f)=%13.5e\n", p[4]);
    printf("\n");
}

double remzf(x)
double x;
{
    double y;
    y = exp(x);
    return (y);
}

