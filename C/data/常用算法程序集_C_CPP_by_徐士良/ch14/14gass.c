
#include "math.h"
#include "14errf.c"
double gass(a, d, x)
double a, d, x;
{
    double y;

    if (d <= 0.0) {
        d = 1.0e-10;
    }

    y = 0.5 + 0.5 * errf((x - a) / (sqrt(2.0) * d));
    return (y);
}

