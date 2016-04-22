/*======================================================
//函数名：bb
//功能描述：双边法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（斜率的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
//#include "rungekuttainvh.c"

int bb(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* f1, *f2, *f3, *p, *q, x;
    int k = 1, i;
    q = (double*)malloc(sizeof(double) * n);
    p = (double*)malloc(sizeof(double) * n); /* 微分方程斜率*/
    f1 = (double*)malloc(sizeof(double) * n);
    f2 = (double*)malloc(sizeof(double) * n);
    f3 = (double*)malloc(sizeof(double) * n);

    if (q == NULL || p == NULL || f2 == NULL || f3 == NULL || f1 == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    rungekuttainvh(y, n, f, h, 1, a);        /* 用龙格-库塔法计算前2个初值*/

    do {
        x = a + k * h;
        f(&y[(k - 1)*n], f1, x - h);         /* x(k-1)处的f*/
        f(&y[k * n], f2, x);                 /* x(k)处的f*/

        for (i = 0; i < n; i++) {            /* 预报p*/
            p[i] = -4.0 * y[k * n + i] + 5.0 * y[(k - 1) * n + i] + 2.0 * h *
                   (2.0 * f2[i] + f1[i]);
        }

        f(p, f3, x + h);                     /* 预报x(k+1)处的f*/

        for (i = 0; i < n; i++) {
            /* 预报c*/
            q[i] = 4.0 * y[k * n + i] - 3.0 * y[(k - 1) * n + i] + 2.0 * h / 3.0 *
                   (f3[i] - 2.0 * f2[i] - 2.0 * f1[i]);
            y[(k + 1)*n + i] = 0.5 * (p[i] + q[i]); /* 计算最终结果*/
        }

        k++;
    } while (k < m);                         /* 循环*/

    free(p);
    free(f2);
    free(f3);
    free(f1);
    free(q);
    return (1);
}


