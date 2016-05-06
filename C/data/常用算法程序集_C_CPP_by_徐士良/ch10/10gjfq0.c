
#include "stdio.h"
#include "10gjfq.c"
main()
{
    int i;
    void  gjfqf(double, double [], int, double []);
    double y[2], z[2][11];
    double t, h, eps;
    t = 0.0;
    h = 0.1;
    eps = 0.00001;
    y[0] = 1.0;
    y[1] = 0.0;
    gjfq(t, h, 2, y, eps, 11, z, gjfqf);
    printf("\n");

    for (i = 0; i <= 10; i++) {
        t = i * h;
        printf("t=%7.3f  y(0)=%13.5e  y(1)=%13.5e\n",
               t, z[0][i], z[1][i]);
    }

    printf("\n");
}

void gjfqf(t, y, n, d)
int n;
double t, y[], d[];
{
    t = t;
    n = n;
    d[0] = -y[1];
    d[1] = y[0];
    return;
}

