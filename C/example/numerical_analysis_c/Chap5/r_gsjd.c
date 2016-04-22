/*======================================================
// 函数名：r_gsjd
// 功能描述：用高斯消去法解线性方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int r_gsjd(a, b, x, n, eps)
double* a, *b, *x, eps;
int n;
{
    int i, j, k, l, v, exis, *exjs;
    double tmp, d;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer exis NULL\n");
        return (0);
    }

    exjs = malloc(n * sizeof(int));        /* 为列交换记录分配空间并检测是否成功*/

    if (exjs == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (k = 0; k < n; k++) {
        d = 0.0;

        for (i = k; i < n; i++)                         /* 此循环用于选取主元*/
            for (j = k; j < n; j++) {
                l = i * n + j;
                tmp = fabs(a[l]);                             /* 求元素的模*/

                if (tmp > d) {
                    d = tmp;
                    exis = i;
                    exjs[k] = j;
                }
            }

        if (d < eps) {                                  /* 判断主元是否过小*/
            free(exjs);
            printf("failed.\n");
            return (0);                                   /* 若主元过小则退出程序*/
        }

        if (exis != k) {                                  /* 判断是否需要行交换*/
            for (j = 0; j < n; j++) {                     /* 进行行交换*/
                l = k * n + j;
                v = exis * n + j;
                tmp = a[l];
                a[l] = a[v];
                a[v] = tmp;
            }

            tmp = b[k];                              /* 常数向量也要进行行交换*/
            b[k] = b[exis];
            b[exis] = tmp;
        }

        if (exjs[k] != k)                                /* 判断是否需要列交换*/
            for (i = 0; i < n; i++) {                    /* 进行列交换*/
                l = i * n + k;
                v = i * n + exjs[k];
                tmp = a[l];
                a[l] = a[v];
                a[v] = tmp;
            }

        l = k * n + k;                             /* 取倒数将除法转化为乘法*/
        a[l] = 1.0 / a[l];

        for (j = k + 1; j < n; j++) {
            v = k * n + j;
            a[v] = a[v] * a[l];
        }

        b[k] = a[l] * b[k];                         /* 常数向量的归一化计算*/

        for (i = 0; i < n; i++) {                   /* 消元计算*/
            if (i != k) {
                for (j = k + 1; j < n; j++) {
                    a[i * n + j] -= a[i * n + k] * a[k * n + j];
                }

                b[i] -= a[i * n + k] * b[k];          /* 常数向量也要进行消元计算*/
            }
        }
    }

    for (i = 0; i < n; i++) {                   /* 现在的b就是解向量*/
        x[i] = b[i];
    }

    for (k = n - 1; k >= 0; k--) {             /* 依照列交换的历史进行结果恢复*/
        if (exjs[k] != k) {                        /* 判断是否需要恢复*/
            tmp = x[k];                            /* 恢复解的顺序*/
            x[k] = x[exjs[k]];
            x[exjs[k]] = tmp;
        }
    }

    free(exjs);                                  /* 释放分配的空间*/
    return (1);                                /* 求解成功，返回1*/
}
