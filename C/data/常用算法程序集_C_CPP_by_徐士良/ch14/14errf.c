
#include "14gam2.c"
double errf(x)
double x;
{
    double y;

    if (x >= 0.0) {
        y = gam2(0.5, x * x);
    } else {
        y = -gam2(0.5, x * x);
    }

    return (y);
}

