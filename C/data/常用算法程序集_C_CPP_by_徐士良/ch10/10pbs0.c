
#include "stdio.h"
#include "10pbs.c"
main()
{
    int i;
    void  pbsf(double, double [], int, double []);
    double t, h, eps, y[2];
    t = 0.0;
    h = 0.1;
    eps = 0.000001;
    y[0] = 1.0;
    y[1] = 0.0;
    printf("\n");
    printf("t=%7.3f  y(0)=%13.5e  y(1)=%13.5e\n", t, y[0], y[1]);

    for (i = 0; i <= 9; i++) {
        pbs(t, h, 2, y, eps, pbsf);
        t = t + h;
        printf("t=%7.3f  y(0)=%13.5e  y(1)=%13.5e\n", t, y[0], y[1]);
    }

    printf("\n");
}

void pbsf(t, y, n, d)
int n;
double t, y[], d[];
{
    t = t;
    n = n;
    d[0] = -y[1];
    d[1] = y[0];
    return;
}

