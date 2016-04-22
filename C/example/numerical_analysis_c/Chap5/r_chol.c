#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/*======================================================
//函数名：r_chol
//功能描述：全选主元的Cholesky分解
//输入参数：mat 指向待分解的矩阵的指针
            n 矩阵阶数
            u   指向返回的下三角阵的指针
            eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int r_chol(mat, n, u, eps)
double* mat, *u, eps;
int n;
{
    int i, j, k;
    double t;

    if ((mat == NULL) || (u == NULL)) {                 /* 检测指针是否为空*/
        printf("One of the pointer is NULL\n");           /* 若为空则打印错误消息，函数结束*/
        return (0);
    }

    for (i = 0; i < n; i++) {                           /* 将u矩阵赋初值为零矩阵*/
        for (j = 0; j < n; j++) {
            u[i * n + j] = 0.0;
        }
    }

    if (fabs(mat[0]) <
        eps) {                    /* 因要做除数并开根号，需要检查其范围*/
        printf("Failed.\n");
        return (0);
    }

    u[0] = sqrt(mat[0]);                                    /* 递推求解*/

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            t = 0.0;

            for (k = 0; k < j; k++) {                     /* 求解U[i,j]中的求和部分*/
                t = t + u[i * n + k] * u[j * n + k];
            }

            u[i * n + j] = (mat[i * n + j] - t) / u[j * n + j]; /* 求解U[i,j]*/
        }

        t = 0.0;

        for (k = 0; k < i; k++) {
            t = t + u[i * n + k] * u[i * n + k];
        }

        t = mat[i * n + i] - t;

        if (t < eps) {                                  /* 检查其范围*/
            printf("Failed.\n");
            return (0);
        }

        u[i * n + i] = sqrt(t);                         /* 求解U[i,i]*/
    }

    return (1);
}
