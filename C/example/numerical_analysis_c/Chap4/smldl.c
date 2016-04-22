/*======================================================
//函数名：smldl
//功能描述：全选主元的LDL分解
//输入参数：mat 指向待分解的矩阵的指针
            n 矩阵阶数
            L   指向返回的下三角阵的指针
            D   指向返回存放对角元素的数组的指针
            eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int smldl(mat, n, L, D, eps)
double* mat, *L, *D, eps;
int n;
{
    int i, j, k;
    double t;

    if ((mat == NULL) || (L == NULL) || (D == NULL)) { /* 检测指针是否为空*/
        printf("One of the pointer is NULL\n");            /* 若为空则打印错误消息，函数结束*/
        return (0);
    }

    for (i = 0; i < n; i++) {                            /* 将L矩阵赋初值为单位阵*/
        for (j = 0; j < n; j++) {
            L[i * n + j] = 0.0;
        }

        L[i * n + i] = 1.0;
    }

    D[0] = mat[0];

    if (fabs(D[0]) <
        eps) {                            /* 因要做除数，需要检查其范围*/
        printf("Failed.\n");
        return (0);
    }                                                 /* 递推求解*/

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            t = 0.0;

            for (k = 0; k < j; k++) {                     /* 求解Lij中的求和部分*/
                t = t + L[i * n + k] * L[j * n + k] * D[k];
            }

            L[i * n + j] = (mat[i * n + j] - t) / D[j];   /* 求解Lij*/
        }

        t = 0.0;

        for (k = 0; k < i; k++) {
            t = t + L[i * n + k] * L[i * n + k] * D[k];
        }

        D[i] = mat[i * n + i] - t;                      /* 求解D[i]*/

        if (fabs(D[i]) < eps) {                         /* 检查其范围*/
            printf("Failed.\n");
            return (0);
        }
    }

    return (1);
}
