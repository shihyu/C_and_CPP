/*======================================================
// 函数名：lsq
// 功能描述：最小二乘拟合
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点的个数
//           p 指向存放pp个拟合多项式系数的数组的指针
//           pp 拟合多项式次数+1
//           s 指向数组的指针，存放4个数据，返回的依次是： 误差的平方和,
//             误差的绝对值的最大值、误差的绝对值之和,x0的平均值
// 返回值：  整型。若拟合成功则返回1,否则返回0
=========================================================*/
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
int lsq(x, y, n, p, pp, s)
double* x, *y, *p, *s;
int n, pp;
{
    int i, j, k;
    double a, b, d0, d1, d2, c, t;
    double* q0, *q1, *q2, *x0;                           /* 存放正交多项式Q的系数*/
    double* q0y, *q1y, *q2y;                        /* 存放正交多项式Q在各点上的值*/

    if (!(x && y && p && s)) {                        /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0);
    }

    q0 = (double*)malloc(pp * sizeof(double));        /* 分配空间并检测是否成功*/
    q1 = (double*)malloc(pp * sizeof(double));
    q2 = (double*)malloc(pp * sizeof(double));

    if (!(q0 && q1 && q2)) {
        free(q0);
        free(q1);
        free(q2);
        printf("Memory alloc Failed\n");
        return (0);
    }

    x0 = (double*)malloc(n * sizeof(double));
    q0y = (double*)malloc(n * sizeof(double));        /* 分配空间并检测是否成功*/
    q1y = (double*)malloc(n * sizeof(double));
    q2y = (double*)malloc(n * sizeof(double));

    if (!(x && q0y && q1y && q2y)) {
        free(x);
        free(q0y);
        free(q1y);
        free(q2y);
        printf("Memory alloc Failed\n");
        return (0);
    }

    t = 0.0;

    for (k = 0; k < n; k++) {
        t = t + x[k] / n;
    }

    s[3] = t;

    for (k = 0; k < n; k++) {
        x0[k] = x[k] - t;
    }

    for (i = 0; i < pp; i++) {                        /* 设初值*/
        q0[i] = 0.0;
        q1[i] = 0.0;
        q2[i] = 0.0;
        p[i] = 0.0;
    }

    for (k = 0; k < n; k++) {
        q0y[k] = 1.0;
    }

    q0[0] = 1;                                        /* Q0的系数*/
    c = 0.0;
    d0 = n;

    for (k = 0; k < n; k++) {                         /* 计算c0*/
        c = c + y[k] / d0;
    }

    p[0] = c;                                      /* 拟合多项式P(x)的系数*/
    q1[0] = 0.0;
    q1[1] = 1.0;                                      /* Q1的系数*/
    d1 = 0.0;
    c = 0.0;

    for (k = 0; k < n; k++) {                         /* 计算d1和c1*/
        t =  x0[k];
        q1y[k] = t;                                     /* Q1在数据点上的值*/
        d1 = d1 + t * t;
        c = c + t * y[k];
    }

    c = c / d1;
    p[0] = p[0] + c * q1[0];                         /* 更新拟合多项式*/
    p[1] = p[1] + c * q1[1];

    for (i = 2; i < pp; i++) {
        a = 0.0;

        for (k = 0; k < n; k++) {
            a = a + x0[k] * q1y[k] * q1y[k];
        }

        a = a / d1;                                    /* alphai*/
        b = d1 / d0;                                   /* beta*/
        d2 = 0;
        c = 0;

        for (k = 0; k < n; k++) {                      /* 计算Qi的函数值和c,d*/
            t = (x0[k] - a) * q1y[k] - b * q0y[k];
            q2y[k] = t;
            d2 = d2 + t * t;
            c = c + t * y[k];
        }

        c = c / d2;
        q2[0] = -a * q1[0] - b * q0[0];                /* 计算Qi的系数*/
        p[0] = p[0] + c * q2[0];                       /* 更新P(x)的系数*/

        for (j = 1; j <= i; j++) {
            q2[j] = q1[j - 1] - a * q1[j] - b * q0[j];
            p[j] = p[j] + c * q2[j];
        }

        d0 = d1;
        d1 = d2;                              /* 循环使用变量*/

        for (k = 0; k < n; k++) {                      /* 循环使用数组*/
            q0y[k] = q1y[k];
            q1y[k] = q2y[k];
        }

        for (j = 0; j <= i; j++) {
            q0[j] = q1[j];
            q1[j] = q2[j];
        }
    }

    s[0] = 0.0;
    s[1] = 0.0;
    s[2] = 0.0;

    for (i = 0; i < n; i++) {
        t = p[pp - 1];

        for (k = pp - 2; k >= 0; k--) {
            t = p[k] + t * x0[i];
        }

        t = t - y[i];

        if (fabs(t) > s[2]) {
            s[2] = fabs(t);
        }

        s[0] = s[0] + t * t;
        s[1] = s[1] + fabs(t);
    }

    free(q0);
    free(q1);
    free(q2);                  /* 释放空间*/
    free(x);
    free(q0y);
    free(q1y);
    free(q2y);
    return (1);
}
