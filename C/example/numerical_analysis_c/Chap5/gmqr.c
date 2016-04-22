/*======================================================
// 函数名：gmqr
// 功能描述：用QR分解法解对称方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           m 方程的个数，n 未知数个数，
//           eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int gmqr(a, b, x, m, n, eps)
double* a, *b, *x, eps;
int n;
{
    int i, k;
    double* c, *q, t;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    if (m < n) {
        printf("m<n, QR decomposition failed\n");
        return (0);
    }

    c = (double*)malloc(m * sizeof(double));
    q = (double*)malloc(m * m * sizeof(double));      /* 分配空间并检测是否成功*/

    if ((c == NULL) || (q == NULL)) {
        free(c);                                      /* 释放空间*/
        free(q);
        printf("Memory alloc failed\n");
        return (0);
    }

    i = r_mqr(a, m, n, q, eps);                    /* 调用函数进行QR分解*/

    if (i == 0) {                                  /* 判断是否分解成功*/
        free(c);                                      /* 释放空间*/
        free(q);
        printf("QR decomposition failed\n");
        return (0);
    }

    for (i = 0; i < n; i++) {                      /* 求出c*/
        t = 0.0;

        for (k = 0; k < m; k++) {
            t = t + q[k * m + i] * b[k];
        }

        c[i] = t;
    }

    for (i = n - 1; i >= 0; i--) {                 /* 求出解向量x*/
        t = 0.0;

        for (k = i + 1; k < n; k++) {
            t = t + a[i * n + k] * x[k];
        }

        x[i] = (c[i] - t) / a[i * n + i];
    }

    free(c);                                      /* 释放空间*/
    free(q);
    return (1);
}