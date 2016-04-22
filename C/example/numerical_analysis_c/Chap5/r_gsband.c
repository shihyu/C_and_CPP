#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*======================================================
// 函数名：r_sband
// 功能描述：用高斯消去法解带型方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，h 半带宽
//           eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int r_gsband(a, b, x, n, h, eps)
double* a, *b, *x, eps;
int n;
{
    int i, j, k, l, v, p;
    double tmp;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    for (k = 0; k < n; k++) {
        l = k * n + k;
        p = (k + h) < (n - 1) ? (k + h) : (n - 1);     /* p=min(k+h, n-1)*/

        if (fabs(a[l]) < eps) {                        /* 判断主元是否过小*/
            printf("failed.\n");
            return (0);                                  /* 若主元过小则退出程序*/
        }

        a[l] = 1.0 / a[l];                            /* 取倒数将除法转化为乘法*/

        for (j = k + 1; j <= p; j++) {                /* 归一化计算*/
            v = k * n + j;
            a[v] = a[l] * a[v];
        }

        b[k] = b[k] * a[l];                           /* 常数向量的归一化计算*/

        for (i = k + 1; i <= p; i++) {                 /* 消元计算*/
            for (j = k + 1; j <= p; j++) {
                a[i * n + j] -= a[i * n + k] * a[k * n + j];
            }

            b[i] -= a[i * n + k] * b[k];               /* 常数向量也要进行消元计算*/
        }
    }

    x[n - 1] = b[n - 1];                           /* 第一个解可直接读出*/

    for (i = n - 2; i >= 0; i--) {                 /* 继续进行回代，求出解向量*/
        p = (i + h) < (n - 1) ? (i + h) : (n - 1);  /* p=min(i+h, n-1)*/
        tmp = 0.0;

        for (j = i + 1; j <= p; j++) {
            tmp = tmp + a[i * n + j] * x[j];
        }

        x[i] = b[i] - tmp;
    }

    return (1);                                  /* 求解成功，返回1*/
}
