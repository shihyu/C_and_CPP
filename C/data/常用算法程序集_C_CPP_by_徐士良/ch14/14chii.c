
#include "14gam2.c"
double chii(x, n)
double x;
int n;
{
    double y;

    if (x < 0.0) {
        x = -x;
    }

    y = gam2(n / 2.0, x / 2.0);
    return (y);
}

