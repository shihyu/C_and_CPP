#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*======================================================
// 函数名：smcg
// 功能描述：用共轭梯度法解对称正定方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，
//           eps 精度要求，iter 最多迭代次数。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int smcg(a, b, x, n, eps, iter)
double* a, *b, *x, eps;
int n, iter;
{
    int i, j, k, piter;
    double* s, *r, t;
    double ta, alpha, tb, tb2, beta;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    s = (double*)malloc(n * sizeof(double));         /* 分配空间并检测是否成功*/
    r = (double*)malloc(n * sizeof(double));

    if ((s == NULL) || (r == NULL)) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (i = 0; i < n; i++) {
        r[i] = b[i];                                 /* 初始残差*/
        x[i] = 0.0;                                  /* 初始解为0*/
        s[i] = b[i];                                 /* 初始搜索方向*/
    }

    tb = 0.0;

    for (k = 0; k < n; k++) {                      /* 初始的tb值*/
        tb = tb + r[k] * r[k];
    }

    piter = 0;

    while ((tb > eps) && (piter < iter) && (piter < n)) {
        ta = 0.0;

        for (k = 0; k < n; k++) {                 /* 求解步长的ta'值*/
            t = 0.0;

            for (j = 0; j < n; j++) {
                t = t + a[k * n + j] * s[j];
            }

            ta = ta + s[k] * t;
        }

        alpha = tb / ta;                         /* 步长alpha的值*/

        for (k = 0; k < n; k++) {                 /* 更新的解*/
            x[k] = x[k] + alpha * s[k];
        }

        for (k = 0; k < n; k++) {                    /* 更新残差*/
            t = 0.0;

            for (j = 0; j < n; j++) {
                t = t + a[k * n + j] * x[j];
            }

            r[k] = b[k] - t;
        }

        tb2 = 0.0;

        for (k = 0; k < n; k++) {                    /* 更新搜索方向*/
            tb2 = tb2 + r[k] * r[k];
        }

        beta = tb2 / tb;

        for (k = 0; k < n; k++) {
            s[k] = r[k] + beta * s[k];
        }

        tb = tb2;
        piter++;                                     /* 更新迭代次数*/
    }

    free(s);
    free(r);
    return (1);
}
