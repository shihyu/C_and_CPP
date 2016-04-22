/*=============================================================
// 函 数 名：r2fft (x,n,y)
// 功能描述：两个实数序列同时进行傅里叶变换，需要fft函数的支持。
// 输入参数：x（变换初始值），n（系数个数）、y（变换后序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"

int r2fft(x1, x2, n, y1, y2)
int n;
double* x1, *x2;
struct c_comp* y1, *y2;
{
    int i, j, k, nn;
    struct c_comp* x, *y;

    k = log(n - 0.5) / log(2.0) + 1;            /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;                               /* 判断n是否是2的整数幂，不是的话退出程序*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        return (0);
    }

    x = (struct c_comp*)malloc(n * sizeof(struct c_comp));
    y = (struct c_comp*)malloc(n * sizeof(struct c_comp));

    for (i = 0; i < n; i++) {                   /* 组合*/
        x[i].rmz = x1[i];
        x[i].imz = x2[i];
    }

    fft(x, n, y);                                   /* 进行傅立叶变换*/
    y1[0].rmz = y[0].rmz;
    y1[0].imz = 0.0;
    y2[0].rmz = y[0].imz;                           /* 求出第一个点*/
    y2[0].imz = 0.0;

    for (k = 1; k <= n / 2; k++) {
        j = n - k;
        y1[k].rmz = 0.5 * (y[k].rmz + y[j].rmz);    /* 求出前半部分*/
        y1[k].imz = 0.5 * (y[k].imz - y[j].imz);
        y2[k].rmz = 0.5 * (y[k].imz + y[j].imz);
        y2[k].imz = -0.5 * (y[k].rmz - y[j].rmz);
        y1[j].rmz = y1[k].rmz;                     /* 求出后半部分*/
        y1[j].imz = -y1[k].imz;
        y2[j].rmz = y2[k].rmz;
        y2[j].imz = -y2[k].imz;
    }

    free(x);
    free(y);
    return (1);
}