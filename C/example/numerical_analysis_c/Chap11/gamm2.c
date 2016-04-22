/*=============================================================
// 函 数 名：gamm2
// 功能描述：求解不完全伽马函数的值
// 输入参数：a 自变量a的值。要求a>0。
//           x 自变量x的值，要求x>=0。
//         e1 精度要求，当两次递推的值变化率小于e1时，认为已收敛
//         e0 极小的数值，接近浮点数能表示的最小数据。为避免除零，将除数设置的值
// 返 回 值：不完全伽马函数的值
//==============================================================*/
#include "stdio.h"
#include "math.h"
#include "gammln.c"
#define NMAX 100

double gamm2(a, x, e1, e0)
double a, x, e1, e0;
{
    int n;
    double t, del, gln;
    double an, bn, c, d;            /* 计算连分式级数需要的变量*/

    if ((x < 0.0) || (a <= 0)) {
        printf("x<0.0 or a<=0.0\n");
        return (0.0);
    }

    if (x < e0) {
        return (0.0);
    }

    gln = gammln(a);

    if (x < (a + 1.0)) {          /* 调用求和级数*/
        del = 1.0 / a;             /*gamm(a)/gamm(a+1)=1/a*/
        t = 1.0 / a;

        for (n = 1; n < NMAX; n++) {
            del = del * x / (a + n);
            t = t + del;

            if (fabs(del) < fabs(t)*e1) {     /* 级数部分已经收敛*/
                t = t * exp(-x + a * log(x) - gln);
                return (t);
            }
        }

        printf(" iteration too many times\n");    /* 经过NMAX次迭代没有收敛*/
        return (0.0);
    } else {                      /* 使用连分式级数*/
        bn = x + 1.0 - a;           /* 已经计算了第一节连分式*/
        c = 1.0 / e0;
        d = 1.0 / bn;
        t = d;

        for (n = 1; n < NMAX; n++) {
            an = n * (a - n);          /* 此节的系数a*/
            bn = bn + 2.0;             /* 此节的系数b*/
            d = an * d + bn;
            c = bn + an / c;

            if (fabs(d) < e0) {        /* 若小于e0，则认为是0*/
                d = e0;
            }

            if (fabs(c) < e0) {
                c = e0;
            }

            d = 1.0 / d;
            del = d * c;
            t = t * del;

            if (fabs(del - 1.0) < e1) {   /* 级数部分已经收敛*/
                t = exp(-x + a * log(x) - gln) * t;
                t = 1.0 - t;
                return (t);
            }
        }

        printf(" iteration too many times\n");    /* 经过NMAX次迭代没有收敛*/
        return (0.0);
    }
}
