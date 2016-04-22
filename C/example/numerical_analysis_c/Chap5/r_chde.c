#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "r_chol.c"
/*======================================================
// 函数名：r_chde
// 功能描述：用cholesky分解法解对称正定实系数矩阵方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int r_chde(a, b, x, n, eps)
double* a, *b, *x, eps;
int n;
{
    int i, k;
    double* u, *y, t;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    u = (double*)malloc(n * n * sizeof(double));     /* 分配空间并检测是否成功*/
    y = (double*)malloc(n * sizeof(double));

    if ((u == NULL) || (y == NULL)) {
        printf("Memory alloc failed\n");
        return (0);
    }

    i = r_chol(a, n, u, eps);                      /* 调用函数进行cholesky分解*/

    if (i == 0) {                                  /* 判断是否分解成功*/
        printf("Cholesky decomposition failed\n");
        return (0);
    }

    for (i = 0; i < n; i++) {                      /* 解出y*/
        t = 0.0;

        for (k = 0; k < i; k++) {
            t = t + u[i * n + k] * y[k];
        }

        y[i] = (b[i] - t) / u[i * n + i];
    }

    for (i = n - 1; i >= 0; i--) {                 /* 求出解向量x*/
        t = 0.0;

        for (k = i + 1; k < n; k++) {
            t = t + u[k * n + i] * x[k];
        }

        x[i] = (y[i] - t) / u[i * n + i];
    }

    free(u);                                       /* 释放空间*/
    free(y);
    return (1);
}
