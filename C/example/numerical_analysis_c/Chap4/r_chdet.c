/*======================================================
//函数名：r_chdet
//功能描述：求对称正定矩阵的行列式值
//输入参数：mat(输入的矩阵) n(矩阵阶数) eps(精度)
//返回值：矩阵的行列式值
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double r_chdet(mat, n, eps)
int n;
double* mat, eps;
{
    int i, j, k, l, v;
    double det;
    double* cpmat;

    if (mat == NULL) {                             /* 检查输入的指针是否为空*/
        printf("matrix pointer is NULL.\n");
        return (0.0);
    }

    cpmat = (double*)malloc(n * n * sizeof(
                                double)); /* 将输入矩阵的内容拷贝一份，以免破坏*/

    for (i = 0; i < n * n; i++) {
        cpmat[i] = mat[i];
    }

    det = 1.0;                                       /* 赋初值*/

    for (k = 0; k < n; k++) {
        l = k * n + k;

        for (j = 0; j < k; j++) {                    /* 求出Lkk*/
            v = k * n + j;
            cpmat[l] = cpmat[l] - cpmat[v] * cpmat[v];
        }

        if (cpmat[l] < eps) {                        /* 判断矩阵是否为正定*/
            printf("matrix is Not positive definite.\n");
            return (0.0);
        }

        cpmat[l] = sqrt(cpmat[l]);
        det = det * cpmat[l];                            /* 更新det*/

        for (i = k + 1; i < n; i++) {                   /* 求出Lik*/
            v = i * n + k;

            for (j = 0; j < k; j++) {
                cpmat[v] = cpmat[v] - cpmat[i * n + j] * cpmat[k * n + j];
            }

            cpmat[v] = cpmat[v] / cpmat[l];
        }
    }

    det = det * det;                                   /* 行列式值是det的平方*/
    free(cpmat);
    return (det);
}
