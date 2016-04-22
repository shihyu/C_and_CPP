/*======================================================
//函数名：r_mrank
//功能描述：求实矩阵的秩
//输入参数：mat(输入的矩阵) m(矩阵行数) p(矩阵列数) eps(精度)
//返回值：运行成功则返回矩阵的秩，失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int r_mrank(mat, m, n, eps)
double* mat, eps;
int m, n;
{
    int i, j, k, p, is, js, l, v, rank;
    double tmp, pivot;
    double* cpmat;

    if (mat == NULL) {            /* 检查输入指针是否为空*/
        printf("matrix pointer is Null.\n");
        return (0);
    }

    cpmat = (double*)malloc(m * n * sizeof(
                                double)); /* 将输入矩阵的内容拷贝一份，以免破坏*/

    for (i = 0; i < m * n; i++) {
        cpmat[i] = mat[i];
    }

    p = m < n ? m : n;            /* 求出m和n中的较小者，即秩的最大值*/
    rank = 0;

    for (k = 0; k < p; k++) {
        pivot = 0.0;                  /* 选主元*/

        for (i = k; i < m; i++)
            for (j = k; j < n; j++) {
                tmp = fabs(cpmat[i * n + j]);

                if (tmp > pivot) {
                    pivot = tmp;
                    is = i;                 /* 记录下主元的位置*/
                    js = j;
                }
            }

        if (pivot < eps) {            /* 主元小于精度值时，认为高斯消元已经完成*/
            return (rank);
        }

        rank++;                   /* 主元不为零，秩加1*/

        if (is != k)              /* 判断是否需要进行行交换*/
            for (j = k; j < n; j++) {       /* 进行行交换*/
                l = k * n + j;
                v = is * n + j;
                tmp = cpmat[l];
                cpmat[l] = cpmat[v];
                cpmat[v] = tmp;
            }

        if (js != k)
            for (i = k; i < m; i++) {       /* 进行列交换*/
                l = i * n + k;
                v = i * n + js;
                tmp = cpmat[l];
                cpmat[l] = cpmat[v];
                cpmat[v] = tmp;
            }

        for (i = k + 1; i < m; i++) {     /* 消去*/
            tmp = cpmat[i * n + k] / cpmat[k * n + k]; /* 减少除法的次数*/

            for (j = k + 1; j < n; j++) { /* 进行消去*/
                cpmat[i * n + j] -= tmp * cpmat[k * n + j];
            }
        }
    }

    free(cpmat);
    return (rank);
}
