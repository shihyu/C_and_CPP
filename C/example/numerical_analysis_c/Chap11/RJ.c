/*=============================================================
// 函 数 名：RJ
// 功能描述：求解第三类椭圆积分的退化形式的值,需要RC和RF函数的支持
// 输入参数：x 求值的自变量
//           y 求值的自变量
//           z 求值的自变量
//           p 求值的自变量
// 返 回 值：第三类椭圆积分的退化形式的值
//==============================================================*/
#include "stdlib.h"
#include "math.h"
double RJ(x, y, z, p)
double x, y, z, p;
{
    double ll, f, s, eps, rc0, a, b, a0, b0, flag;
    double t, t1, t2, t3, t4, t5, t6;
    double xt, yt, zt, pt;
    eps = 1.0e-10;

    if (x < 0 || y < 0 || z < 0 || (x + y) < eps || (x + z) < eps ||
        (z + y) < eps || fabs(p) < eps) { /* 检查自变量范围*/
        printf("Parameters incorrect\n");
        return (0.0);
    }

    s = 0.0;
    f = 4.0;

    if (p < 0.0) {
        t1 = y;                                              /* t1存放xyz中最大者*/
        t = x;                                               /* t 存放xyz中最小者*/

        if (x > y) {
            t = y;
            t1 = x;
        }

        if (t > z) {
            t = z;
        }

        if (t1 < z) {
            t1 = z;
        }

        y = x + y + z - t -
            t1;                               /* 按x<y<z排列是为了防止计算溢出*/
        x = t;
        z = t1;
        a0 = 1.0 / (y - p);
        b0 = a * (z - y) * (y - x);
        rc0 = RC(x * z / y, p * (p + b0) / y);
        p = p + b0;
    }

    do {
        t1 = sqrt(x);
        t2 = sqrt(y);
        t3 = sqrt(z);
        ll = t1 * (t2 + t3) + t2 * t3;
        a = (p * (t1 + t2 + t3) + t1 * t2 * t3);
        a = a * a;
        b = (p + ll);
        b = p * b * b;
        f = f / 4.0;
        s = s + f * RC(a, b);
        x = (x + ll) / 4.0;                                    /* 更新x,y,z,p*/
        y = (y + ll) / 4.0;
        z = (z + ll) / 4.0;
        p = (p + ll) / 4.0;
        t = (x + y + z + p + p) / 5.0;
        xt = 1.0 - x / t;
        yt = 1.0 - y / t;
        zt = 1.0 - z / t;
        pt = 1.0 - p / t;
        t1 = fabs(xt) > fabs(yt) ? fabs(xt) : fabs(yt);
        t2 = fabs(zt) > fabs(pt) ? fabs(zt) : fabs(pt);
        flag = t1 > t2 ? t1 : t2;
    } while (flag >
             0.0015);                                   /* 这个阈值用于判断x和y充分接近*/

    t1 = xt * (yt + zt) + yt *
         zt;                            /* 用泰勒展开计算积分值*/
    t2 = xt * yt * zt;
    t3 = pt * pt;
    t4 = t1 - 3.0 * t3;
    t5 = t2 + 2.0 * pt * (t1 - t3);
    t6 = pt;
    t = (1.0 + t4 * (-3.0 / 14.0 + t4 / 88.0 - 9.0 * t5 / 52.0) +
         t2 * (1.0 / 6.0 + t6 * (-3.0 / 11.0 + 3.0 * t6 / 26.0)) +
         t1 * t6 * (1.0 / 3.0 - 3.0 * t6 / 22.0) - t3 * t6 / 3.0) / (t * sqrt(t));
    t = 3.0 * s + f * t;                                      /* 乘上系数*/

    if (p < 0) {
        t = a0 * (b0 * t + 3.0 * (rc0 - RF(x, y,
                                           z)));    /* 最后计算RF(x,y,z)，速度比较快，因为已经迭代过*/
    }

    return (t);
}