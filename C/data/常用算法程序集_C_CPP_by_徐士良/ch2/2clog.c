
#include "math.h"
void clog(x, y, u, v)
double x, y, *u, *v;
{
    double p;
    p = log(sqrt(x * x + y * y));
    *u = p;
    *v = atan2(y, x);
    return;
}

