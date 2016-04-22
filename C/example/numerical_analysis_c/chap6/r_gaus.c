#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*======================================================
// 函数名：r_gaus
// 功能描述：用高斯消去法解线性方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int r_gaus(a, b, x, n, eps)
double* a, *b, *x, eps;
int n;
{
    int i, j, k, l, v, is, *js;
    double tmp, d;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    js = malloc(n * sizeof(int));        /* 为列交换记录分配空间并检测是否成功*/

    if (js == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (k = 0; k < n; k++) {
        d = 0.0;

        for (i = k; i < n; i++)                         /* 此循环用于选取主元*/
            for (j = k; j < n; j++) {
                l = i * n + j;
                tmp = fabs(a[l]);                             /* 求元素的绝对值*/

                if (tmp > d) {
                    d = tmp;
                    is = i;
                    js[k] = j;
                }
            }

        if (d < eps) {                                  /* 判断主元是否过小*/
            free(js);
            printf("failed.\n");
            return (0);                                   /* 若主元过小则退出程序*/
        }

        if (is != k) {                                  /* 判断是否需要行交换*/
            for (j = 0; j < n; j++) {                     /* 进行行交换*/
                l = k * n + j;
                v = is * n + j;
                tmp = a[l];
                a[l] = a[v];
                a[v] = tmp;
            }

            tmp = b[k];                                  /* 常数向量也要进行行交换*/
            b[k] = b[is];
            b[is] = tmp;
        }

        if (js[k] != k)                                /* 判断是否需要列交换*/
            for (i = 0; i < n; i++) {                      /* 进行列交换*/
                l = i * n + k;
                v = i * n + js[k];
                tmp = a[l];
                a[l] = a[v];
                a[v] = tmp;
            }

        l = k * n + k;
        a[l] = 1.0 / a[l];                            /* 取倒数将除法转化为乘法*/

        for (j = k + 1; j < n; j++) {                 /* 归一化计算*/
            v = k * n + j;
            a[v] = a[l] * a[v];
        }

        b[k] = b[k] * a[l];                           /* 常数向量的归一化计算*/

        for (i = k + 1; i < n; i++) {                 /* 消元计算*/
            for (j = k + 1; j < n; j++) {
                a[i * n + j] -= a[i * n + k] * a[k * n + j];
            }

            b[i] -= a[i * n + k] * b[k];               /* 常数向量也要进行消元计算*/
        }
    }

    x[n - 1] = b[n - 1];                           /* 第一个解可直接读出*/

    for (i = n - 2; i >= 0; i--) {                 /* 继续进行回代，求出解向量*/
        tmp = 0.0;

        for (j = i + 1; j < n; j++) {
            tmp = tmp + a[i * n + j] * x[j];
        }

        x[i] = b[i] - tmp;
    }

    for (k = n - 1; k >= 0; k--) {             /* 依照列交换的历史进行结果恢复*/
        if (js[k] != k) {                        /* 判断是否需要恢复*/
            tmp = x[k];                            /* 恢复解的顺序*/
            x[k] = x[js[k]];
            x[js[k]] = tmp;
        }
    }

    free(js);                                  /* 释放分配的空间*/
    return (1);                                /* 求解成功，返回1*/
}
