/*======================================================
//函数名：r_mlu
//功能描述：全选主元的LU分解
//输入参数：mat 指向待分解的矩阵的指针
            n 矩阵阶数
            L,U 指向返回的下三角阵和下三角阵的指针
            P,Q 指向返回的初等行列变换阵的指针
            eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int r_mlu(mat, n, L, U, P, Q, eps)
double* mat, *L, *U, *P, *Q, eps;
int n;
{
    int i, j, k, is, js, l, v, kk, ii;
    double tmp, pivot;

    if ((mat == NULL) || (L == NULL) || (U == NULL) || (P == NULL) ||
        (Q == NULL)) { /* 检测指针是否为空*/
        printf("One of the pointer is NULL\n");            /* 若为空则打印错误消息，函数结束*/
        return (0);
    }

    for (i = 0; i < n;
         i++) {                            /* 为P，Q矩阵赋初值为单位阵*/
        for (j = 0; j < n; j++) {
            P[i * n + j] = 0.0;
            Q[i * n + j] = 0.0;
        }

        P[i * n + i] = 1.0;
        Q[i * n + i] = 1.0;
    }

    for (k = 0; k < n - 1; k++) {
        pivot = 0.0;                                         /* 选取主元*/

        for (i = k; i < n; i++)
            for (j = k; j < n; j++) {
                tmp = fabs(mat[i * n + j]);

                if (tmp > pivot) {
                    pivot = tmp;
                    is = i;
                    js = j;
                }
            }

        if (pivot < eps) {                                  /* 判断主元是否为0*/
            printf("Fail\n");                                 /* 若主元为0,则函数结束*/
            return (0);
        }

        if (is != k) {                                      /* 判断是否需要行交换*/
            for (j = 0; j < n; j++) {
                l = k * n + j;                                   /* 对待分解矩阵进行行交换*/
                v = is * n + j;
                tmp = mat[l];
                mat[l] = mat[v];
                mat[v] = tmp;

                tmp = Q[l];                                      /* 对P矩阵进行行交换*/
                Q[l] = Q[v];
                Q[v] = tmp;
            }
        }

        if (js != k) {                                      /* 判断是否需要列交换*/
            for (i = 0; i < n; i++) {
                l = i * n + k;                                 /* 对待分解矩阵进行列交换*/
                v = i * n + js;
                tmp = mat[l];
                mat[l] = mat[v];
                mat[v] = tmp;

                tmp = P[l];                                     /* 对Q矩阵进行列交换*/
                P[l] = P[v];
                P[v] = tmp;
            }
        }

        kk = k * n + k;
        tmp = 1.0 / mat[kk];                               /* 更新矩阵a中的元素*/

        for (i = k + 1; i < n; i++) {
            l = i * n + k;
            mat[l] = mat[l] * tmp;

            for (j = k + 1; j < n; j++) {
                v = i * n + j;
                mat[v] = mat[v] - mat[l] * mat[k * n + j];
            }
        }
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {                           /* 计算L矩阵和U矩阵*/
            l = i * n + j;

            if (j < i) {
                L[l] = mat[l];
                U[l] = 0.0;
            } else if (j == i) {
                L[l] = 1.0;
                U[l] = mat[l];
            } else {
                L[l] = 0.0;
                U[l] = mat[l];
            }
        }

    return (1);
}
