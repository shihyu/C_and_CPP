/*======================================================
//函数名：r_matmul
//功能描述：两个实矩阵相乘
//输入参数：a(左矩阵) b(右矩阵)  c(结果矩阵)
            m(左矩阵行数) p(左矩阵列数) n(右矩阵列数)
//返回值：运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"

int r_matmul(a, b, m, p, n, c)
double* a, *b, *c;
int m, p, n;
{
    int i, j, k;
    double tmp;

    if (!(m > 0 && p > 0 && n > 0)) {          /* 检查输入矩阵的阶数*/
        printf("Dimension of a matrix is incorrect\n");
        return (0);
    }

    if (a == NULL || b == NULL || c == NULL) { /* 检查输入指针是否为空*/
        printf("The matrix pointer is NULL\n");
        return (0);
    }

    for (i = 0; i < m; i++)           /* 循环遍历矩阵c中的每个元素*/
        for (j = 0; j < n; j++) {
            tmp = 0.0;                /* 初值先存在临时变量中*/

            for (k = 0; k < p; k++) {     /* 循环累加*/
                tmp += a[i * p + k] * b[k * n + j];
            }

            c[i * n + j] = tmp;               /* 将得到的结果放入矩阵c中*/
        }

    return (1);
}
