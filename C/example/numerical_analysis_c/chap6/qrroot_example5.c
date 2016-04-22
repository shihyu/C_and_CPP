#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include"qrroot.c"

void main()
{
    int i, itmax = 60;
    double eps = 0.000001;                           /* 精度*/
    static double u[5], v[5];                        /* 存放根的矩阵*/
    static double a[6] = {3.0, 2.0, 4.5, 2.2, 1.0, 2.1}; /* 降幂系数*/

    i = qrroot(a, 5, u, v, eps, itmax);                 /* 调用函数*/

    if (i > 0)                                       /* 成功求值输出*/
        for (i = 0; i <= 4; i++) {
            printf("%13.7e +j %13.7e\n", u[i], v[i]);
        }

    printf("\n");
}