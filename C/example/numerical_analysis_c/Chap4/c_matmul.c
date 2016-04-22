#include "stdio.h"
#include "stdlib.h"
#include "c_comp.c"             /* 需要调用复数运算的算法*/

/*======================================================
//函数名：cmat_mul
//功能描述：两个复矩阵相乘
//输入参数：a(左矩阵) b(右矩阵)  c(结果矩阵)
            m(左矩阵行数) p(左矩阵列数) n(右矩阵列数)
//返回值：运行成功则返回1,失败则返回0
=========================================================*/
int c_matmul(a, b, m, p, n, c)
struct c_comp* a, *b, *c;
int m, p, n;
{
    int i, j, k;
    struct c_comp tmp1, tmp2;

    if (!(m > 0 && p > 0 && n > 0)) {   /* 检测输入矩阵的阶数*/
        printf("Err:(c_mat_mul)Dimension of a matrix is incorrect\n");
        return (0);
    }

    if (a == NULL || b == NULL || c == NULL) { /* 检查输入指针是否为空*/
        printf("Err:(c_mat_mul)The matrix pointer is NULL\n");
        return (0);
    }

    for (i = 0; i < m; i++)         /* 循环编历矩阵c中的每个元素*/
        for (j = 0; j < n; j++) {
            tmp1.rmz = 0.0;         /* 初值先存入复临时变量中*/
            tmp1.imz = 0.0;

            for (k = 0; k < p; k++) {   /* 循环累加*/
                c_comp_product(&a[i * m + k], &b[k * m + j], &tmp2);
                c_comp_plus(&tmp1, &tmp2, &tmp1);
            }

            c[i * n + j].rmz = tmp1.rmz;    /* 将计算的结果存入矩阵c中*/
            c[i * n + j].imz = tmp1.imz;
        }

    return (1);
}
