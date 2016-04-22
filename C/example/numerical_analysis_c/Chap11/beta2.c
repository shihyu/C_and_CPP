/*=============================================================
// 函 数 名：beta2
// 功能描述：求解不完全贝塔积分的值
// 输入参数：a 自变量a的值。要求a>0。
//           b 自变量b的值。要求b>0。
//           x 自变量x的值，要求0<=x<=1。
//         e1 精度要求，当两次递推的值变化率小于e1时，认为已收敛
// 返 回 值：不完全贝塔函数的值
//==============================================================*/
#include "stdio.h"
#include "math.h"
#include "gammln.c"
#define NMAX 100                         /* 迭代的最大次数*/
#define EULER 0.5772156649
#define FPMIN 1.0e-30                    /* 为防止除0使用的常数*/

double beta2(a, b, x, e1)
double a, b, x, e1;
{
    double t;
    double subcf();                          /* 计算连分式级数需要的变量和函数*/

    if ((x < 0.0) || (x > 1.0) || (a <= 0.0) || (b <= 0.0)) {
        printf("Bad input parameter\n");
        return (0.0);
    } else if (x == 0.0) {                           /* x为0的情况*/
        t = 0.0;
        return (t);
    } else if (x == 1.0) {                           /* x为1的情况*/
        t = 1.0;
        return (t);
    } else if (x > (a + 1.0) / (a + b + 2.0)) {
        t = exp(gammln(a + b) - gammln(a) - gammln(b) + a * log(x) + b * log(
                    1.0 - x)); /* 系数*/
        t = 1.0 - t * subcf(b, a, 1.0 - x, e1) / b;    /* 使用连分式级数*/
        return (t);
    } else {
        t = exp(gammln(a + b) - gammln(a) - gammln(b) + a * log(x) + b * log(
                    1.0 - x)); /* 系数*/
        t = t * subcf(a, b, x, e1) / a;                /* 使用连分式级数*/
        return (t);
    }
}

static double subcf(a, b, x, e1)
double a, b, x, e1;
{
    int n;
    double t, del, an, c, d;
    c = 1.0;
    d = 1.0 - (a + b) * x / (a + 1.0);

    if (fabs(d) < FPMIN) {
        d = FPMIN;
    }

    d = 1.0 / d;
    t = d;

    for (n = 1; n < NMAX; n++) {
        an = n * (b - n) * x / ((a + 2.0 * n - 1.0) * (a + 2.0 *
                                n)); /* 第2n节的系数a,此节的系数b为1*/
        d = an * d + 1.0;                          /* 计算d*/
        c = 1.0 + an / c;                          /* 计算c*/

        if (fabs(d) < FPMIN) {                     /* 检查cd的范围*/
            d = FPMIN;
        }

        if (fabs(c) < FPMIN) {
            c = FPMIN;
        }

        d = 1.0 / d;
        del = d * c;
        t = t * del;
        an = -(a + n) * (a + b + n) * x / ((a + 2.0 * n) * (a + 1.0 + 2.0 *
                                           n)); /* 第2n+1节*/
        d = 1.0 + an * d;
        c = 1.0 + an / c;

        if (fabs(d) < FPMIN) {
            d = FPMIN;
        }

        if (fabs(c) < FPMIN) {
            c = FPMIN;
        }

        d = 1.0 / d;
        del = d * c;
        t = t * del;

        if (fabs(del - 1.0) < e1) {                /* 级数部分已经收敛*/
            return (t);
        }
    }

    printf("iteration not converged.");          /* 没有收敛*/
    return (t);
}
