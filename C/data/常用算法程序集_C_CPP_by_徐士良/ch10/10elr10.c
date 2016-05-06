
#include "stdio.h"
#include "10elr1.c"
main()
{
    int i, j;
    void  elr1f(double, double [], int, double []);
    double y[3], z[3][11], t, h, x;
    y[0] = -1.0;
    y[1] = 0.0;
    y[2] = 1.0;
    t = 0.0;
    h = 0.01;
    elr1(t, y, 3, h, 11, z, elr1f);
    printf("\n");

    for (i = 0; i <= 10; i++) {
        x = i * h;
        printf("t=%5.2f\n", x);

        for (j = 0; j <= 2; j++) {
            printf("y(%d)=%13.5e  ", j, z[j][i]);
        }

        printf("\n");
    }

    printf("\n");
}

void elr1f(t, y, n, d)
int n;
double t, y[], d[];
{
    t = t;
    n = n;
    d[0] = y[1];
    d[1] = -y[0];
    d[2] = -y[2];
    return;
}

