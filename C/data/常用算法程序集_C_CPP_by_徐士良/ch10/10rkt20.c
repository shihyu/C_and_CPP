
#include "stdio.h"
#include "10rkt2.c"
main()
{
    int i;
    void  rkt2f(double, double [], int, double []);
    double t, h, eps, y[2];
    y[0] = 0.0;
    y[1] = 1.0;
    t = 0.0;
    h = 0.1;
    eps = 0.00001;
    printf("\n");
    printf("t=%7.3f  y(0)=%e  y(1)=%13.5e\n", t, y[0], y[1]);

    for (i = 1; i <= 10; i++) {
        rkt2(t, h, y, 2, eps, rkt2f);
        t = t + h;
        printf("t=%7.3f  y(0)=%e  y(1)=%13.5e\n", t, y[0], y[1]);
    }
}

void rkt2f(t, y, n, d)
int n;
double t, y[], d[];
{
    t = t;
    n = n;
    d[0] = y[1];
    d[1] = -y[0];
    return;
}

