/*=============================================================
// 函 数 名：p2c (y,n,a)
// 功能描述：将多项式由点表示转化为系数表示
// 输入参数：y（提供的点值），n（y的长度），a（计算得到的多项式系数）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"
int p2c(y, n, a)
int n;
struct c_comp* a, *y;
{
    int i, j, k, nn;
    int p2c1();                          /* 首先声明一个要调用的子函数*/
    k = log(n - 0.5) / log(2.0) + 1;     /* 求出log2(n)*/
    nn = 1;

    for (i = 0; i < k; i++) {            /* 检测点个数是否是2的整数次幂*/
        nn = nn << 1;
    }

    if (nn != n) {
        printf("(p2c)n should be 2^k.\n");
        return (0);
    }

    j = p2c1(y, n, a);                   /* 调用子函数求解求和符号中的部分*/

    if (j) {
        for (i = 0; i < n; i++) {       /* 将子函数返回的结果除以n*/
            a[i].rmz /= n;
            a[i].imz /= n;
        }
    }

    return (j);
}

int p2c1(y, n, a)
int n;
struct c_comp* a, *y;
{
    int i, j, k;
    struct c_comp xn, x, t;
    struct c_comp* a0, *a1, *y0, *y1;

    if (n == 1) {                          /* n=1时，唯一系数a与y相等*/
        a[0].rmz = y[0].rmz;
        a[0].imz = y[0].imz;
        return (1);
    }

    k = n >> 1;                           /*k是n的一半，就是两个小规模问题分配空间的大小*/
    a0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    a1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y0 = (struct c_comp*)malloc(k * sizeof(struct c_comp));
    y1 = (struct c_comp*)malloc(k * sizeof(struct c_comp));

    if ((a0 == NULL) || (a1 == NULL) || (y0 == NULL) || (y1 == NULL)) {
        printf("(p2c)memory alloc failed.\n");
        return (0);
    }

    for (i = 0; i < k; i++) {              /* 将问题分成两段*/
        j = 2 * i;
        y0[i].rmz = y[j].rmz;
        y0[i].imz = y[j].imz;
        y1[i].rmz = y[j + 1].rmz;
        y1[i].imz = y[j + 1].imz;
    }

    i = p2c1(y0, k, a0);                   /* 对两段分别求解*/
    j = p2c1(y1, k, a1);

    if (i && j) {                          /* 若两段求解成功，则将两部分解综合起来*/
        xn.rmz = cos(-2 * PI / n);
        xn.imz = sin(-2 * PI / n);
        x.rmz = 1.0;
        x.imz = 0.0;

        for (i = 0; i < k; i++) {
            c_comp_product(&x, &a1[i], &t);
            c_comp_plus(&a0[i], &t, &a[i]);   /* 一加一减，完成了函数值的综合*/
            c_comp_sub(&a0[i], &t, &a[i + k]);
            c_comp_product(&xn, &x,
                           &x);      /* x与xn相乘，结果放在x中，第k次综合时的x就是xn^k*/
        }
    }

    free(y0);
    free(y1);
    free(a0);
    free(a1);
    return (1);
}
