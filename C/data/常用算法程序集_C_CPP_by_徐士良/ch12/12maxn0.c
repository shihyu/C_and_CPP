
#include "stdio.h"
#include "12maxn.c"
main()
{
    int js[2];
    double eps, x[3];
    double maxnf(double [], int, int);
    eps = 0.000001;
    x[0] = 0.0;
    x[1] = 0.0;
    maxn(x, 2, eps, 10, js, maxnf);
    printf("\n");
    printf("js(0)=%3d\n", js[0]);
    printf("x(0)=%13.5e\n", x[0]);
    printf("x(1)=%13.5e\n", x[1]);

    if (js[1] < 0.0) {
        printf("MIN:  ");
    }

    if (js[1] > 0.0) {
        printf("MAX:  ");
    }

    printf("z=%13.5e\n", x[2]);
    printf("\n");
}

double maxnf(x, n, j)
int n, j;
double x[];
{
    double y;
    n = n;

    switch (j) {
    case 0:
        y = (x[0] - 1.0) * (x[0] - 10.0)
            + (x[1] + 2.0) * (x[1] + 2.0) + 2.0;
        break;

    case 1:
        y = 2.0 * (x[0] - 1.0);
        break;

    case 2:
        y = 2.0 * (x[1] + 2.0);
        break;

    default:
        {}
    }

    return (y);
}

