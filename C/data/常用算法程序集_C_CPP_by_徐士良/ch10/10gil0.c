
#include "stdio.h"
#include "10gil.c"
main()
{
    int i, j;
    void  gilf(double, double [], int, double []);
    double t, h, eps;
    double q[3] = {0.0, 0.0, 0.0};
    double y[3] = {0.0, 1.0, 1.0};
    t = 0.0;
    h = 0.1;
    eps = 0.000001;
    printf("\n");
    printf("t=%7.3f\n", t);

    for (i = 0; i <= 2; i++) {
        printf("y(%d)=%13.5e  ", i, y[i]);
    }

    printf("\n");

    for (j = 1; j <= 10; j++) {
        gil(t, h, y, 3, eps, q, gilf);
        t = j * h;
        printf("t=%7.3f\n", t);

        for (i = 0; i <= 2; i++) {
            printf("y(%d)=%13.5e  ", i, y[i]);
        }

        printf("\n");
    }
}

void gilf(t, y, n, d)
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

