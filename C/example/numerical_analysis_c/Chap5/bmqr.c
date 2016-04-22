#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "r_mqr.c"                         /* QR分解的函数*/
/*======================================================
// 函数名：bmqr
// 功能描述：用迭代法解病态方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，
//           eps 精度要求，iter 最多迭代次数。
// 返回值：整型。运行成功则返回迭代次数,失败则返回0
=========================================================*/
int bmqr(a, b, x, n, eps, iter)
double* a, *b, *x, eps;
int n, iter;
{
    int i, k, piter;
    double* c, *q, *r, *e, t, fr;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer is NULL\n");
        return (0);
    }

    c = (double*)malloc(n * sizeof(double));
    q = (double*)malloc(n * n * sizeof(double));   /* 分配空间并检测是否成功*/
    r = (double*)malloc(n * sizeof(double));
    e = (double*)malloc(n * sizeof(double));

    if ((c == NULL) || (q == NULL) || (r == NULL) || (e == NULL)) {
        printf("Memory alloc failed\n");
        return (0);
    }

    i = r_mqr(a, n, n, q, eps * eps);              /* 调用函数进行QR分解*/

    if (i == 0) {                                  /* 判断是否分解成功*/
        printf("QR decomposition failed\n");
        return (0);
    }

    for (i = 0; i < n; i++) {
        t = 0.0;

        for (k = 0; k < n; k++) {
            t = t + q[k * n + i] * b[k];
        }

        c[i] = t;                                    /* 求出c*/
        r[i] = c[i];                                 /* 初始残差*/
        x[i] = 0.0;                                  /* 初始解为0*/
        e[i] = 0.0;                                  /* 初始修正为0*/
    }

    fr = 1.0;
    piter = 0;

    while ((fr > eps) && (piter < iter)) {
        for (i = n - 1; i >= 0; i--) {               /* 解出修正量e*/
            t = 0.0;

            for (k = i + 1; k < n; k++) {
                t = t + a[i * n + k] * e[k];
            }

            e[i] = (r[i] - t) / a[i * n + i];
            x[i] = x[i] + e[i];
        }

        for (i = 0; i < n; i++) {                    /* 更新残差*/
            t = 0.0;

            for (k = i; k < n; k++) {
                t = t + a[i * n + k] * x[k];
            }

            r[i] = r[i] - t;
        }

        fr = 0.0;                                    /* 更新修正误差*/

        for (i = 0; i < n; i++) {
            t = fabs(e[i]) / (1 + fabs(x[i]));

            if (t > fr) {
                fr = t;
            }
        }

        piter++;                                     /* 更新迭代次数*/
    }

    free(c);                                       /* 释放空间*/
    free(q);
    free(r);
    free(e);
    return (piter);
}
