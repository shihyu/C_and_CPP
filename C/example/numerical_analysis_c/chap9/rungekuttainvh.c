/*======================================================
//函数名：rungekuttainvh
//功能描述：定步长四阶龙格库塔算法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（斜率的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int rungekuttainvh(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* k1, *k2, *k3, *k4, *ytemp, x;
    int k = 0, i;
    k1 = (double*)malloc(sizeof(double) * n);    /* 微分方程斜率*/
    k2 = (double*)malloc(sizeof(double) * n);
    k3 = (double*)malloc(sizeof(double) * n);
    k4 = (double*)malloc(sizeof(double) * n);
    ytemp = (double*)malloc(sizeof(double) * n);

    if (k1 == NULL || k2 == NULL || k3 == NULL || k4 == NULL || ytemp == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {
        x = a + k * h;
        f(&y[k * n], k1, x);                       /* k1*/

        for (i = 0; i < n; i++) {
            ytemp[i] = y[k * n + i] + h * k1[i] / 2.0;
        }

        f(ytemp, k2, x + h / 2.0);                 /* k2*/

        for (i = 0; i < n; i++) {
            ytemp[i] = y[k * n + i] + h * k2[i] / 2.0;
        }

        f(ytemp, k3, x + h / 2.0);                 /* k3*/

        for (i = 0; i < n; i++) {
            ytemp[i] = y[k * n + i] + h * k3[i];
        }

        f(ytemp, k4, x + h);                       /* k4*/

        for (i = 0; i < n; i++) {                  /* 计算此处的函数值*/
            y[(k + 1)*n + i] = y[k * n + i] + h / 6.0 * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] +
                               k4[i]);
        }

        k++;
    } while (k < m);

    free(k1);
    free(k2);
    free(k3);
    free(k4);
    free(ytemp);
    return (1);
}

