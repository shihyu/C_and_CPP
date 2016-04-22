/*======================================================
// 函数名：goldsch
// 功能描述：黄金分割搜索法求极值
// 输入参数：a 初始区间的端点
//           b 初始区间的中间点
//           c 初始区间的另一个端点
//           f 函数指针
//           xopt 指针，指向极值点的坐标
//         eps 精度限度
// 返回值：  函数的极小值
=========================================================*/

#include "stdio.h"
#include "math.h"
#define G2 0.38196601

double goldsch(a, b, c, f, xopt, eps)
double a, b, c, eps;
double (*f)(double);
double* xopt;
{
    double f0, f1, f2, f3, t;

    if (fabs(c - b) > fabs(b - a)) {     /* 在较大的一段中求t*/
        t = b + G2 * (c - b);
    } else {
        t = b;
        b = b - G2 * (b - a);
    }

    f1 = (*f)(b);
    f2 = (*f)(t);

    while (fabs(c - a) > eps * (fabs(b) + fabs(t))) {
        if (f2 > f1) {                    /* 新区间为[a b t]*/
            c = t;                        /* 更新c*/
            t = b;                        /* 更新b和t*/
            b = b - G2 * (b - a);
            f3 = f2;
            f2 = f1;
            f1 = (*f)(b);
        } else {                          /* 新区间为[b t c]*/
            a = b;                         /* 更新a*/
            b = t;
            t = t + G2 * (c - t);          /* 计算新t*/
            f0 = f1;
            f1 = f2;
            f2 = (*f)(t);
        }
    }

    if (f1 < f2) {                         /* 返回较好的一个值*/
        *xopt = b;
        return (f1);
    } else {
        *xopt = t;
        return (f2);
    }
}
