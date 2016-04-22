/*=============================================================
// 函 数 名：c2p (a,n,y)
// 功能描述：将多项式由系数表示转化为点表示
// 输入参数：a（多项式系数），n（系数个数）、y（计算出的点值）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"

int c2p(a, n, y)
int n;
struct c_comp* a, *y;
{
    int i, k, nn;
    int c2p0();
    k = log(n - 0.5) / log(2.0) + 1;  /* 求出k，使2^k>=n>2^(k-1) */
    nn = 1;

    for (i = 0; i < k; i++) {       /* 判断n是否是2的整数幂，不是的话退出程序*/
        nn = nn << 1;
    }

    if (nn != n) {
        printf("n should be 2^k.\n");
        return (0);
    }

    k = c2p0(a, n, y);
    return (k);
}

int c2p0(a, n, y)
int n;
struct c_comp* a, *y;
{
    int i, j, k;
    struct c_comp xn, x, t;
    struct c_comp* a0, *a1, *y0, *y1;

    if (n == 1) {
        /* 当只有一个系数时，函数值就是这个系数*/
        y[0].rmz = a[0].rmz;
        y[0].imz = a[0].imz;
        return (1);
    }

    k = n >> 1;       /* k是n的一半，即两个小规模问题需要分配空间大小*/
    a0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    a1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));

    if ((a0 == NULL) || (a1 == NULL) || (y0 == NULL) || (y1 == NULL)) {
        printf("(c2p0)memory alloc failed.\n");
        return (0);
    }

    for (i = 0; i < k; i++) {         /* 将多项式分成两半*/
        j = 2 * i;
        a0[i].rmz = a[j].rmz;
        a0[i].imz = a[j].imz;
        a1[i].rmz = a[j + 1].rmz;
        a1[i].imz = a[j + 1].imz;
    }

    i = c2p0(a0, k, y0);              /* 递归调用此函数*/
    j = c2p0(a1, k, y1);

    if (i && j) {                     /* 将得到的两部分函数值综合起来*/
        xn.rmz = cos(2 * PI / n);
        xn.imz = sin(2 * PI / n);
        x.rmz = 1.0;
        x.imz = 0.0;

        for (i = 0; i < k; i++) {
            c_comp_product(&x, &y1[i], &t);               /* 一加一减，完成了函数值的综合*/
            c_comp_plus(&y0[i], &t, &y[i]);
            c_comp_sub(&y0[i], &t, &y[i + k]);
            c_comp_product(&xn, &x,
                           &x);  /* x与xn相乘，结果放在x中，第k次综合时的x就是xn^k*/
        }
    }

    free(y0);
    free(y1);
    free(a0);
    free(a1);
    return (1);
}
