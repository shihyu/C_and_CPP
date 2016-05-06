
#include "math.h"
#include "stdio.h"
#include "7cmtc.c"
main()
{
    int m;
    double x, y, b, eps, cmtcf(double, double);
    x = 0.5;
    y = 0.5;
    b = 1.0;
    m = 10;
    eps = 0.00001;
    cmtc(&x, &y, b, m, eps, cmtcf);
    printf("\n");
    printf("z=%13.5e +j %13.5e\n", x, y);
    printf("\n");
}

double cmtcf(x, y)
double x, y;
{
    double u, v, z;
    u = x * x - y * y + x - y - 2.0;
    v = 2.0 * x * y + x + y + 2.0;
    z = sqrt(u * u + v * v);
    return (z);
}

