/*======================================================
//函数名：sdminv
//功能描述：对称正定矩阵原地求逆
//输入参数：mat 指向待分解的矩阵的指针
            n 矩阵阶数
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int sdminv(mat, n, eps)
double* mat;
int n;
double eps;
{
    int i, j, k;
    double p, q, *c;

    if (mat == NULL) {                 /* 检查指针是否为空*/
        printf("The matrix pointer is NULL\n");
        return (0);
    }

    c = (double*)malloc(n * sizeof(double)); /* 为临时变量分配空间并检查是否成功*/

    if (c == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (k = 0; k < n; k++) {        /* 循环求解*/
        p = mat[0];

        if (p < eps) {                /* 判断是否满足正定的条件*/
            printf("Fail to invert\n");
            free(c);
            return (0);
        }

        p = 1.0 / p;                  /* 将要进行的多次除法转化为乘法*/

        for (i = 1; i < n - k; i++) { /* 求出矩阵下三角部分前n-k行的值*/
            q = mat[i * n];
            c[i] = -q * p;

            for (j = 1; j < i + 1; j++) {
                mat[(i - 1)*n + j - 1] = mat[i * n + j] + q * c[j];
            }
        }

        for (i = n - k; i < n; i++) { /* 求出矩阵下三角部分中第n-k行至第n-1行的值*/
            q = mat[i * n];
            c[i] = q * p;

            for (j = 1; j < i + 1; j++) {
                mat[(i - 1)*n + j - 1] = mat[i * n + j] + q * c[j];
            }
        }

        mat[n * n - 1] = p;           /* 求出矩阵下三角部分中第n行的值*/

        for (i = 1; i < n; i++) {
            mat[(n - 1)*n + i - 1] = c[i];
        }
    }

    for (i = 0; i < n - 1; i++)      /* 依据对称性对矩阵的上三角部分进行赋值*/
        for (j = i + 1; j < n; j++) {
            mat[i * n + j] = mat[j * n + i];
        }

    free(c);                         /* 释放分配的空间*/
    return (1);
}
