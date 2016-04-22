/*=============================================================
// 函 数 名：hadma1 (x,n,y)
// 功能描述：哈达玛变换
// 输入参数：x（变换初始值），n（系数个数）、y（变换后序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
int hadma(y, n, x)
int n;
double* x, *y;
{
    int i, j, k, nn;
    double t;
    int hadma1(double * x, int n, double * y); /* 因为要递归调用，所以先声明*/
    k = log(n - 0.5) / log(2.0) + 1;            /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;                              /* 判断n是否是2的整数幂，不是的话退出程序*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        return (0);
    }

    j = hadma1(y, n,
               x);                            /* 调用子函数求解求和符号中的部分*/

    if (j) {
        t = 1.0 / sqrt(n);

        for (i = 0; i < n;
             i++) {                       /* 将子函数返回的结果除以n^0.5*/
            x[i] *= t;
        }
    }

    return (j);
}
int hadma1(x, n, y)
int n;
double* x, *y;
{
    int i, j, k;
    double t;

    if (n == 1) {
        /* 当序列长度为1时，沃尔什变换是它本身*/
        y[0] = x[0];
        return (1);
    }

    k = n >> 1;                        /* k是n的一半，即两个小规模问题需要分配空间大小*/
    i = hadma1(x, k, y);               /* 递归调用此函数，变换前一半*/
    j = hadma1(x + k, k, y + k);           /* 递归调用此函数，变换后一半*/

    if (i && j) {                             /* 将得到的两部分序列综合起来*/
        for (i = 0; i < k; i++) {
            /* 一加一减，完成了序列的综合*/
            t = y[i + k];
            y[i + k] = y[i] - t;
            y[i] = y[i] + t;
        }
    }

    return (1);
}
