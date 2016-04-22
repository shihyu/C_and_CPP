#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "smldl.c"                         /* LDL分解的函数*/
/*======================================================
// 函数名：r_ldl
// 功能描述：用LDL分解法解对称方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int r_ldl(a, b, x, n, eps)
double* a, *b, *x, eps;
int n;
{
    int i, k;
    double* L, *D, *y, *z, t;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    D = (double*)malloc(n * sizeof(double));       /* 分配空间并检测是否成功*/
    L = (double*)malloc(n * n * sizeof(double));
    y = (double*)malloc(n * sizeof(double));
    z = (double*)malloc(n * sizeof(double));

    if ((D == NULL) || (L == NULL) || (y == NULL) || (z == NULL)) {
        printf("Memory alloc failed\n");
        return (0);
    }

    i = smldl(a, n, L, D, eps);                    /* 调用函数进行LDL分解*/

    if (i == 0) {                                  /* 判断是否分解成功*/
        printf("LDL decomposition failed\n");
        return (0);
    }

    for (i = 0; i < n; i++) {                      /* 解出y和z*/
        t = 0.0;

        for (k = 0; k < i; k++) {
            t = t + L[i * n + k] * y[k];
        }

        y[i] = b[i] - t;
        z[i] = y[i] / D[i];
    }

    for (i = n - 1; i >= 0; i--) {                 /* 求出解向量x*/
        t = 0.0;

        for (k = i + 1; k < n; k++) {
            t = t + L[k * n + i] * x[k];
        }

        x[i] = z[i] - t;
    }

    free(D);                                       /* 释放空间*/
    free(L);
    free(y);
    free(z);
    return (1);
}
