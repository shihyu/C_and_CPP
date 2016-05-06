
#include "math.h"
#include "stdio.h"
#include "7dhrt.c"
main()
{
    int i, n;
    int m = 6;
    double x[6];
    double dhrtf(double);
    n = dhrt(-2.0, 5.0, 0.2, 0.000001, x, m, dhrtf);
    printf("M=%d\n", n);

    for (i = 0; i <= n - 1; i++) {
        printf("x(%d)=%13.6e\n", i, x[i]);
    }

    printf("\n");
}

double dhrtf(x)
double x;
{
    double z;
    z = (((((x - 5.0) * x + 3.0) * x + 1.0) * x - 7.0) * x + 7.0) * x - 20.0;
    return (z);
}

