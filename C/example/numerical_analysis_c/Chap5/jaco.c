#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*======================================================
// 函数名：jaco
// 功能描述：用雅克比迭代法解方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求。
//           iter 允许的最多迭代次数
// 返回值：整型。运行成功则返回迭代次数,失败则返回0
=========================================================*/
int jaco(a, b, x, n, eps, iter)
double* a, *b, *x, eps;
int n, iter;
{
    int i, j, piter = 0;
    double fr = 1.0, t, *x2;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    x2 = (double*)malloc(n * sizeof(double));      /* 分配空间并检测是否成功*/

    if (x2 == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (i = 0; i < n; i++)
        if (fabs(a[i * n + i]) < 1e-12) {        /* 因为要做除数，需要检查是否过小*/
            printf("A[%d,%d] is too small,cannot converged", i, i);
            return (0);
        }

    for (i = 0; i < n; i++) {                 /* 对解向量赋初值*/
        x[i] = 0.0;
    }

    while ((fr > eps) && (piter < iter)) {
        fr = 0.0;

        for (i = 0; i < n; i++) {
            t = 0.0;

            for (j = 0; j < i; j++) {
                t = t + a[i * n + j] * x[j];
            }

            for (j = i + 1; j < n; j++) {
                t = t + a[i * n + j] * x[j];
            }

            x2[i] = (b[i] - t) / a[i * n + i];      /* 更新的x值*/
            t = fabs(x2[i] - x[i]) / (1.0 + fabs(x[i])); /* 更新误差*/

            if (t > fr) {
                fr = t;
            }
        }

        for (i = 0; i < n; i++) {
            x[i] = x2[i];
        }

        piter++;                               /* 迭代次数增加1*/
    }

    return (piter);
}
