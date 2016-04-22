/*=============================================================
// 函 数 名：fft (x,n,y)
// 功能描述：离散傅里叶变换
// 输入参数：x（变换初始值），n（系数个数）、y（变换后序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"

int fft(y, n, x)
int n;
struct c_comp* x, *y;
{
    int i, j, k, nn;
    int fft0(struct c_comp * x, int n,
             struct c_comp * y); /* 因为要递归调用，所以先声明*/
    k = log(n - 0.5) / log(2.0) + 1;            /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;                              /* 判断n是否是2的整数幂，不是的话退出程序*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        return (0);
    }

    j = fft0(y, n, x);                          /* 调用子函数计算傅里叶变换*/
    return (j);
}

int fft0(x, n, y)
int n;
struct c_comp* x, *y;
{
    int i, j, k;
    struct c_comp wn, w, t;
    struct c_comp* x0, *x1, *y0, *y1;

    if (n == 1) {
        /* 当序列长度为1时，傅里叶变换是它本身*/
        y[0].rmz = x[0].rmz;
        y[0].imz = x[0].imz;
        return (1);
    }

    k = n >> 1;                  /* k是n的一半，即两个小规模问题需要分配空间大小*/
    x0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    x1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));

    if ((x0 == NULL) || (x1 == NULL) || (y0 == NULL) || (y1 == NULL)) {
        printf("memory xlloc fxiled.\n");
        return (0);
    }                                               /* 将序列分成两半*/

    for (i = 0; i < k; i++) {
        j = 2 * i;
        x0[i].rmz = x[j].rmz;
        x0[i].imz = x[j].imz;
        x1[i].rmz = x[j + 1].rmz;
        x1[i].imz = x[j + 1].imz;
    }                                               /* 递归调用此函数*/

    i = fft0(x0, k, y0);
    j = fft0(x1, k, y1);

    if (i && j) {                             /* 将得到的两部分序列综合起来*/
        wn.rmz = cos(2 * PI / n);
        wn.imz = sin(-2 * PI / n);
        w.rmz = 1.0;
        w.imz = 0.0;

        for (i = 0; i < k; i++) {
            /* 一加一减，完成了序列的综合*/
            c_comp_product(&w, &y1[i], &t);
            c_comp_plus(&y0[i], &t, &y[i]);
            c_comp_sub(&y0[i], &t, &y[i + k]);
            c_comp_product(&wn, &w,
                           &w);    /* w与wn相乘，结果放在w中，第k次综合时的w就是wn^k*/
        }
    }

    free(y0);
    free(y1);
    free(x0);
    free(x1);
    return (1);
}
