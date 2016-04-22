#include "stdio.h"
#include "rpmul.c"
#include "rpdiv.c"
void main()
{
    int i;
    double a[3], b[3], c[5], q[4], r[5];

    for (i = 0; i < 3; i++) {
        a[i] = i + 1;
        b[i] = 2 * i;
    }

    i = rpmul(a, 3, b, 3, c);    /* 调用多项式的乘法，并打印相乘的结果*/

    if (i) {
        printf("c=a*b:\n");

        for (i = 0; i < 5; i++) {
            printf("c[%d]=%3.2f ", i, c[i]);
        }
    }

    printf("\n");
    i = rpdiv(c, 5, b, 3, q, 3, r,
              5); /* 调用多项式的除法，并打印相除的结果，于相乘前做比较*/

    if (i) {
        printf("c/b--Q:\n");

        for (i = 0; i < 3; i++) {
            printf("q[%d]=%3.2f ", i, q[i]);
        }

        printf("\nc/b--R:\n");

        for (i = 0; i < 5; i++) {
            printf("r[%d]=%3.2f ", i, r[i]);
        }

        printf("\n");
    }
}
