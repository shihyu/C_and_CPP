
#include "stdio.h"
#include "10elr2.c"
main()
{
    int i, j;
    void elr2f(double, double [], int, double []);
    double t, h, eps, y[3];
    y[0] = -1.0;
    y[1] = 0.0;
    y[2] = 1.0;
    t = 0.0;
    h = 0.01;
    eps = 0.00001;
    printf("\n");
    printf("t=%5.2f\n", t);

    for (i = 0; i <= 2; i++) {
        printf("y(%d)=%13.5e  ", i, y[i]);
    }

    printf("\n");

    for (j = 1; j <= 10; j++) {
        elr2(t, h, y, 3, eps, elr2f);
        t = t + h;
        printf("t=%5.2f\n", t);

        for (i = 0; i <= 2; i++) {
            printf("y(%d)=%13.5e  ", i, y[i]);
        }

        printf("\n");
    }
}

void elr2f(t, y, n, d)
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

