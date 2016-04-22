/*======================================================
//函数名：toepl
//功能描述：求解托伯利兹方程组
//输入参数：t 指向存放n阶托伯利兹矩阵元素的数组的指针
//          b 指向存放常数向量数组的指针
//          x 指向返回的解向量数组的指针
//          n 矩阵阶数
//          eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int toepl(t, b, x, n, eps)
double* t, *b, *x, eps;
int n;
{
    int i, j, k;
    double beta, s1, s, p, q, *y, *yy;

    if ((t == NULL) || (b == NULL) || (x == NULL)) {   /* 检测指针是否为空*/
        printf("One of the pointer is NULL\n");          /* 若为空则打印错误消息，函数结束*/
        return (0);
    }

    y = (double*)malloc(n * sizeof(double));
    yy = (double*)malloc(n * sizeof(double));

    if ((y == NULL) || (yy == NULL)) {                 /* 分配空间并检测是否成功*/
        printf("Memory alloc failed\n");
        free(y);
        free(yy);
        return (0);
    }

    for (i = 0; i < n; i++) {                          /* 将y和yy数组赋初值为零*/
        y[i] = 0.0;
        yy[i] = 0.0;
    }

    if (fabs(t[0]) <
        eps) {                            /* 因要做除数，需要检查其范围*/
        free(y);
        free(yy);
        printf("Failed.\n");
        return (0);
    }

    y[0] = 1.0 / t[0];                                 /* 设定初值*/
    x[0] = b[0] / t[0];

    for (k = 1; k < n; k++) {                          /* 递推求解*/
        beta = 0.0;

        for (i = 0; i < k; i++) {                        /* 求出beta*/
            beta = beta + t[i + 1] * y[i];
        }

        s1 = 1.0 - beta * beta;

        if (fabs(s1) < eps) {                           /* 因要做除数，需要检查其范围*/
            free(y);
            free(yy);
            printf("Failed.\n");
            return (0);
        }

        p = 1.0 / s1;                                   /* 计算p和s*/
        s = -beta / s1;
        yy[0] = s * y[k - 1];

        for (i = 1; i < k; i++) {                       /* 递推计算yy*/
            yy[i] = p * y[i - 1] + s * y[k - 1 - i];
        }

        yy[k] = p * y[k - 1];
        q = 0.0;

        for (i = 0; i < k; i++) {
            q = q + t[k - i] * x[i];
        }

        s = b[k] - q;                                   /* 递推计算x*/

        for (i = 0; i < k; i++) {
            x[i] = x[i] + s * yy[i];
        }

        x[k] = s * yy[k];

        for (i = 0; i < k + 1; i++) {                   /* 将yy的值赋给y*/
            y[i] = yy[i];
        }
    }

    free(y);
    free(yy);
    return (1);
}
