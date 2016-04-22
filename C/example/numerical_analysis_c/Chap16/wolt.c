/*=============================================================
// 函 数 名：wolt1 (x,n,y)
// 功能描述：沃尔什变换
// 输入参数：x（变换初始值），n（系数个数）、y（变换后序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
int wolt(y, n, x)
int n;
double* x, *y;
{
    int i, j, k, nn;
    double t;
    int wolt1(double * x, int n, double * y); /* 因为要递归调用，所以先声明*/
    k = log(n - 0.5) / log(2.0) + 1;            /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;                              /* 判断n是否是2的整数幂，不是的话退出程序*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        return (0);
    }

    j = wolt1(y, n,
              x);                             /* 调用子函数求解求和符号中的部分*/

    if (j) {
        t = 1.0 / sqrt(n);

        for (i = 0; i < n;
             i++) {                       /* 将子函数返回的结果除以n^0.5*/
            x[i] *= t;
        }
    }

    return (j);
}
int wolt1(x, n, y)
int n;
double* x, *y;
{
    int i, j, k;
    double* x0, *x1, *y0, *y1;

    if (n == 1) {
        /* 当序列长度为1时，沃尔什变换是它本身*/
        y[0] = x[0];
        return (1);
    }

    k = n >> 1;                  /* k是n的一半，即两个小规模问题需要分配空间大小*/
    x0 = (double*)malloc(k * sizeof(double));
    x1 = (double*)malloc(k * sizeof(double));
    y0 = (double*)malloc(k * sizeof(double));
    y1 = (double*)malloc(k * sizeof(double));

    if ((x0 == NULL) || (x1 == NULL) || (y0 == NULL) || (y1 == NULL)) {
        printf("memory xlloc failed.\n");
        return (0);
    }                                               /* 将序列分成两半*/

    for (i = 0; i < k; i++) {
        j = 2 * i;
        x0[i] = x[j];
        x1[i] = x[j + 1];
    }                                               /* 递归调用此函数*/

    i = wolt1(x0, k, y0);
    j = wolt1(x1, k, y1);

    if (i && j) {                             /* 将得到的两部分序列综合起来*/
        for (i = 0; i < k; i++) {
            /* 一加一减，完成了序列的综合*/
            y[i] = y0[i] + y1[i];
            y[i + k] = y0[i] - y1[i];
        }
    }

    free(y0);
    free(y1);
    free(x0);
    free(x1);
    return (1);
}
