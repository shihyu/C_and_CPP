
#include "14beta.c"
double ffff(f, n1, n2)
int n1, n2;
double f;
{
    double y;

    if (f < 0.0) {
        f = -f;
    }

    y = beta(n2 / 2.0, n1 / 2.0, n2 / (n2 + n1 * f));
    return (y);
}

