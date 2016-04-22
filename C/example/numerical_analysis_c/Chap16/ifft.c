/*=============================================================
// 函 数 名：ifft (y,n,x)
// 功能描述：傅里叶逆变换
// 输入参数：y（待变换的序列），n（y的长度），x（变换后的序列）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"
int ifft(y, n, x)
int n;
struct c_comp* x, *y;
{
    int i, j, k, nn;
    int ifft1(struct c_comp * y, int n,
              struct c_comp * x); /* 首先声明一个要调用的子函数*/
    k = log(n - 0.5) / log(2.0) + 1;               /* 求出log2(n)*/
    nn = 1;

    for (i = 0; i < k; i++) {                      /* 检测点个数是否是2的整数次幂*/
        nn = nn << 1;
    }

    if (nn != n) {
        printf("(ifft)n should be 2^k.\n");
        return (0);
    }

    j = ifft1(y, n,
              x);                             /* 调用子函数求解求和符号中的部分*/

    if (j) {
        for (i = 0; i < n; i++) {                     /* 将子函数返回的结果除以n*/
            x[i].rmz /= n;
            x[i].imz /= n;
        }
    }

    return (j);
}

int ifft1(y, n, x)
int n;
struct c_comp* x, *y;
{
    int i, j, k;
    struct c_comp wn, w, t;
    struct c_comp* x0, *x1, *y0, *y1;

    if (n == 1) {                                   /* n=1时，唯一元素x与y相等*/
        x[0].rmz = y[0].rmz;
        x[0].imz = y[0].imz;
        return (1);
    }

    k = n >> 1;                            /*k是n的一半，就是两个小规模问题分配空间的大小*/
    x0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    x1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));

    if ((x0 == NULL) || (x1 == NULL) || (y0 == NULL) || (y1 == NULL)) {
        printf("(ifft)memory xlloc fxiled.\n");
        return (0);
    }

    for (i = 0; i < k; i++) {                      /* 将问题分成两段*/
        j = 2 * i;
        y0[i].rmz = y[j].rmz;
        y0[i].imz = y[j].imz;
        y1[i].rmz = y[j + 1].rmz;
        y1[i].imz = y[j + 1].imz;
    }

    i = ifft1(y0, k, x0);                         /* 对两段分别求解*/
    j = ifft1(y1, k, x1);

    if (i && j) {                                 /* 若两段求解成功，则将两部分解综合起来*/
        wn.rmz = cos(2 * PI / n);
        wn.imz = sin(2 * PI / n);
        w.rmz = 1.0;
        w.imz = 0.0;

        for (i = 0; i < k; i++) {
            c_comp_product(&w, &x1[i], &t);
            c_comp_plus(&x0[i], &t, &x[i]);          /* 一加一减，完成了序列的综合*/
            c_comp_sub(&x0[i], &t, &x[i + k]);
            c_comp_product(&wn, &w,
                           &w);   /* w与wn相乘，结果放在w中，第k次综合时的w就是wn^k*/
        }
    }

    free(y0);
    free(y1);
    free(x0);
    free(x1);
    return (1);
}
