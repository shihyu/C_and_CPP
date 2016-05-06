
#include "14beta.c"
double stdt(t, n)
int n;
double t;
{
    double y;

    if (t < 0.0) {
        t = -t;
    }

    y = 1.0 - beta(n / 2.0, 0.5, n / (n + t * t));
    return (y);
}

