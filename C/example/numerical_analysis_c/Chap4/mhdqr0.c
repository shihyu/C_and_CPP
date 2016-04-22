#include "stdio.h"
#include "mhdqr.c"
main()
{
    int i, itmax = 60;
    double eps = 1e-7;
    double u[5], v[5];
    double a[5][5] = { {1.0, 6.0, -3.0, -1.0, 7.0},
        {8.0, -15.0, 18.0, 5.0, 4.0},
        {0.0, 11.0, 9.0, 15.0, 20.0},
        {0.0, 0.0, 21.0, 30.0, -6.0},
        {0.0, 0.0, 0.0, 3.0, 6.0}
    };

    i = mhdqr(a, 5, u, v, eps, itmax);                /* 调用函数求解并打印结果*/

    if (i > 0) {
        printf("\ndqr eigvalue:\n");

        for (i = 0; i < 5; i++) {
            printf("%9.6f + j(%9.6f)\n", u[i], v[i]);
        }
    }
}
