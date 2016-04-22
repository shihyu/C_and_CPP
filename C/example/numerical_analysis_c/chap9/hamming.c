/*======================================================
//函数名：hamming
//功能描述：哈明方法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（斜率的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
//#include "rungekuttainvh.c"

int hamming(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* c, *f1, *f2, *f3, *f4, *temp, *ptemp, *p, x;
    int k = 3, i;
    c = (double*)malloc(sizeof(double) * n);
    p = (double*)malloc(sizeof(double) * n);  /* 微分方程斜率*/
    f1 = (double*)malloc(sizeof(double) * n);
    f2 = (double*)malloc(sizeof(double) * n);
    f3 = (double*)malloc(sizeof(double) * n);
    f4 = (double*)malloc(sizeof(double) * n);
    ptemp = (double*)malloc(sizeof(double) * n);

    if (c == NULL || p == NULL || f2 == NULL || f3 == NULL || f4 == NULL ||
        f1 == NULL || ptemp == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    rungekuttainvh(y, n, f, h, 3, a);         /* 用龙格-库塔法计算前4个初值*/

    {
        x = a + k * h;
        f(&y[(k - 2)*n], f1, x - 2 * h);      /* x(k-2)处的f*/
        f(&y[(k - 1)*n], f2, x - h);          /* x(k-1)处的f*/
        f(&y[k * n], f3, x);                  /* xk处的f*/

        for (i = 0; i < n; i++) {             /* 预报p*/
            p[i] = y[(k - 3) * n + i] + 4.0 * h / 3.0 * (2.0 * f3[i] - f2[i] + 2.0 *
                    f1[i]);
        }

        f(p, f4, x + h);                      /* 预报x(k+1)处的f*/

        for (i = 0; i < n; i++) {
            /* 预报c*/
            c[i] = 1.0 / 8.0 * (9.0 * y[k * n + i] - y[(k - 2) * n + i] + 3.0 * h *
                                (f4[i] + 2.0 * f3[i] - f2[i]));
            y[(k + 1)*n + i] = c[i] - 9.0 / 121.0 * (c[i] - p[i]); /* 计算最终结果*/
        }

        k++;
    }

    while (k < m) {                           /* 循环*/
        x = a + k * h;
        temp = f1;
        f1 = f2;
        f2 = f3;
        f3 = temp;
        f(&y[k * n], f3, x);

        for (i = 0; i < n; i++) {
            ptemp[i] = y[(k - 3) * n + i] + 4.0 * h / 3.0 * (2.0 * f3[i] - f2[i] + 2.0 *
                       f1[i]);  /* 预报*/
            p[i] = ptemp[i] + 112.0 / 121.0 * (c[i] - p[i]);              /* 预报*/
        }

        f(p, f4, x + h);                                           /* x(k+1)处的f*/

        for (i = 0; i < n; i++) {
            c[i] = 1.0 / 8.0 * (9.0 * y[k * n + i] - y[(k - 2) * n + i] + 3.0 * h *
                                (f4[i] + 2.0 * f3[i] - f2[i]));
            y[(k + 1)*n + i] = c[i] - 9.0 / 121.0 * (c[i] - p[i]);
        }

        k++;
    }

    free(p);
    free(f2);
    free(f3);
    free(f4);
    free(f1);
    free(ptemp);
    free(c);
    return (1);
}


