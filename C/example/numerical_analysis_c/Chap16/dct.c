/*=============================================================
// 函 数 名：dct (x,n,y)
// 功能描述：离散余弦变换
// 输入参数：x（变换初始值），n（系数个数）、y（变换后序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"

int dct(x, n, y)
int n;
double* x, *y;
{
    int i, j, k, nn;
    double t;
    struct c_comp wn, w, t2;
    struct c_comp* x1, *y1;
    x1 = (struct c_comp*)malloc(n * sizeof(struct c_comp));
    y1 = (struct c_comp*)malloc(n * sizeof(struct c_comp));
    k = log(n - 0.5) / log(2.0) + 1;            /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;                                  /* 判断n是否是2的整数幂，不是的话退出程序*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        free(x1);
        free(y1);
        return (0);
    }

    k = n >> 1;

    for (i = 0; i < k; i++) {                /* 将x进行重排 , 前半段*/
        x1[i].rmz = x[2 * i];
        x1[i].imz = 0.0;
    }

    for (i = k; i < n; i++) {                /* 将x进行重排 ,后半段*/
        x1[i].rmz = x[2 * (n - i) - 1];
        x1[i].imz = 0.0;
    }

    j = fft(x1, n, y1);                       /* 调用子函数计算傅里叶变换*/
    t = 1.0 / sqrt(n);
    y[0] = t * y1[0].rmz;
    t = sqrt(2) * t;
    wn.rmz = cos(3.1415926 / 2 / n);
    wn.imz = sin(-3.1415926 / 2 / n);
    w.rmz = 1.0;
    w.imz = 0.0;

    for (i = 1; i < n; i++) {
        c_comp_product(&wn, &w,
                       &w);    /* w与wn相乘，结果放在w中，第k次综合时的w就是wn^k*/
        c_comp_product(&w, &y1[i], &t2);
        y[i] = t * t2.rmz;                   /* 实部为结果*/
    }

    free(x1);
    free(y1);
    return (j);
}