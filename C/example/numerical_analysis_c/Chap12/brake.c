/*======================================================
// 函数名：brake
// 功能描述：确定存在极值的区间
// 输入参数：a 输入初始区间端点，返回时为区间的左端点
//           b 输入初始区间端点，返回时为区间的中间点
//           c 返回时为区间的右端点
//           f 函数指针
// 返回值：  无
=========================================================*/

#include "stdio.h"
#include "math.h"
#define G1 0.61803399
#define GSTEP 100.0
#define TINY 1.0e-20

void brake(a, b, c, f)
double* a, *b, *c;
double (*f)(double);
{
    double u, u2, fu, fa, fb, fc, tmp;
    double r, q, p;                        /* 用于抛物线插值*/

    fa = (*f)(*a);
    fb = (*f)(*b);

    if (fb > fa) {                         /* 确保a->b方向是下降的*/
        tmp = *a;
        *a = *b;
        *b = tmp;
        tmp = fa;
        fa = fb;
        fb = tmp;
    }

    *c = (*b) + G1 * (*b - *a);            /* 区间延伸到点c*/
    fc = (*f)(*c);

    while (fb >= fc) {                      /* 这时需要继续寻找区间*/
        r = (*b - *a) * (fb - fc);           /* fb-fc>=0*/
        q = (*b - *c) * (fb - fa);           /* fb-fa <=0*/
        p = (*b - *c) * q - (*b - *a) * r;   /* p<0.  q与r异号*/
        tmp = q - r;

        if (fabs(tmp) < TINY) {             /* 分母过小*/
            tmp = TINY;
        }

        u = *b - p / (2.0 * tmp);           /* 求出抛物线的极值点u*/
        u2 = *b + GSTEP * (*c - *b);        /* u2限制了u行进的最大步长*/

        if ((*b - u) * (*c - u) < 0.0) {    /* u在b 和c之间*/
            fu = (*f)(u);

            if (fu < fc) {                  /* b u c确定一个存在极小值的区间*/
                if (*b < *c) {              /* 调整后保证a < b < c*/
                    *a = *b;
                    *b = u;
                } else {                    /* 调整后保证a < b < c*/
                    *a = *c;
                    *c = *b;
                    *b = u;
                }

                return;
            } else if (fu > fb) {           /* a b u确定了一个存在极小值的区间*/
                if (*a < u) {
                    *c = u;
                } else {
                    *c = *a;
                    *a = u;
                }

                return;
            }

            u = *c + G1 * (*c - *b);         /* 抛物线确定的u无用*/
            fu = (*f)(u);
        } else if ((*c - u) * (u2 - u) < 0.0) { /* u在c和u2之间*/
            fu = (*f)(u);

            if (fu < fc) {
                *b = *c;
                *c = u;
                u = *c + G1 * (*c - *b);
                fb = fc;
                fc = fu;
                fu = (*f)(u);
            }
        } else if ((u - u2) * (*c - u2) >= 0) { /* 抛物线给出的u值过大，使用u2代替*/
            u = u2;
            fu = (*f)(u);
        } else {
            u = (*c) + G1 * (*c - *b);
            fu = (*f)(u);
        }

        *a = *b;                               /* 更新a,b,c*/
        *b = *c;
        *c = u;
        fa = fb;
        fb = fc;
        fc = fu;
    }

    if (*a > *c) {                      /* [a,c]就是存在极小值的区间*/
        tmp = *a;                       /* 调整成 a<b<c*/
        *a = *c;
        *c = tmp;
    }

    return;
}
