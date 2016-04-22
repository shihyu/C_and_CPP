/*=============================================================
// 函 数 名：expi
// 功能描述：求解指数积分的值
// 输入参数：n 自变量n的值。要求a>0。
//           x 自变量x的值，要求x>=0。
//         e1 精度要求，当两次递推的值变化率小于e1时，认为已收敛
// 返 回 值：不完全伽马函数的值
//==============================================================*/
#include "stdio.h"
#include "math.h"
#define NMAX 100
#define EULER 0.5772156649
#define FPMIN 1.0e-30

double expi(n, x, e1)
int n;
double x, e1;
{
    int i, j;
    double t, t2, del;
    double a, b, c, d;                               /* 计算连分式级数需要的变量*/

    if ((x < 0.0) || (n < 0) || (x == 0.0 && (n < 2))) {
        printf("%2.1f,%d", x, n);
        printf("bad input parameter\n");
        return (0.0);
    } else if (x == 0.0) {                           /* x为0的情况*/
        t = 1.0 / (n - 1.0);
        return (t);
    } else if (n == 0) {                             /* n为0的情况*/
        t = exp(-x) / x;
        return (t);
    } else if (x > 1.0) {                            /* 使用连分式级数*/
        b = x + n;                                     /* 已经计算了第一节连分式*/
        c = 1.0 / FPMIN;
        d = 1.0 / b;
        t = d;

        for (i = 1; i < NMAX; i++) {
            a = -i * (n - 1 + i);                         /* 此节的系数a*/
            b = b + 2.0;                                  /* 此节的系数b*/
            d = a * d + b;
            c = b + a / c;                                /* c总是大于0*/
            d = 1.0 / d;                                  /* d总是大于0*/
            del = d * c;
            t = t * del;

            if (fabs(del - 1.0) < e1) {                   /* 级数部分已经收敛*/
                t = exp(-x) * t;
                return (t);
            }
        }
    } else {                                          /* 使用求和级数*/
        t = (n == 1) ? (-log(x) - EULER) : (1.0 / (n - 1));
        t2 = 1.0;

        for (i = 1; i < NMAX; i++) {
            t2 = -t2 * x / i;

            if (i != (n - 1)) {
                del = -t2 / (i - n + 1);
            } else {
                del = -EULER;                               /* phi(n)的计算*/

                for (j = 1; j < n; j++) {
                    del = del + 1.0 / j;
                }

                del = t2 * (-log(x) + del);
            }

            t = t + del;

            if (fabs(del) < fabs(t)*e1) {                 /* 级数部分已经收敛*/
                return (t);
            }
        }
    }

    printf(" iteration too many times\n");            /* 经过NMAX次迭代没有收敛*/
    return (0.0);
}
