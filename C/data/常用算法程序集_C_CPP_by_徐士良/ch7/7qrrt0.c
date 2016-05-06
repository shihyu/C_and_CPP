
#include "stdio.h"
#include "7qrrt.c"
main()
{
    int i, jt, n;
    double xr[6], xi[6];
    double a[7] = { -30.0, 10.5, -10.5, 1.5, 4.5, -7.5, 1.5};
    double eps;
    eps = 0.000001;
    jt = 60;
    n = 6;
    i = qrrt(a, n, xr, xi, eps, jt);
    printf("\n");

    if (i > 0) {
        for (i = 0; i <= 5; i++) {
            printf("x(%d)=%13.6e  %13.6e j\n", i, xr[i], xi[i]);
        }

        printf("\n");
    }
}

