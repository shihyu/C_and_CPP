/*======================================================
// 函数名：brent
// 功能描述：Brent算法法求极值
// 输入参数：a 初始区间的左端点
//           b 初始区间的中间点
//           c 初始区间的右端点
//           f 函数指针
//           xopt 指针，指向极值点的坐标
//           eps 精度限度
//           itmax 最大迭代次数
// 返回值：  函数的极小值
=========================================================*/

#include "stdio.h"
#include "math.h"
#define G2 0.38196601

double brent(a, b, c, f, xopt, eps, itmax)
double a, b, c, eps;
double (*f)(double);
double* xopt;
int itmax;
{
    int it;
    double xm, x, u, w, v, fx, fu, fw, fv, eps1, eps2, d0, d;
    double p, q, r;                                    /* 用于抛物线插值*/
    x = w = v = b;
    fx = fw = fv = (*f)(b);
    d0 = 0.0;

    for (it = 0; it < itmax; it++) {
        xm = (a + c) * 0.5;
        eps1 = eps * fabs(x) + 1.0e-10;
        eps2 = 2.0 * eps1;

        if ((c - a) * 0.5 < (eps2 - fabs(x - xm))) {    /* 迭代收敛准则*/
            *xopt = x;
            return (fx);
        }

        if (fabs(d0) <= eps1) {                         /* 上次变化太小，用黄金分割法*/
            d0 = (x > xm) ? a - x : c - x;
            d = G2 * d0;
        } else {
            r = (x - w) * (fx - fv);                   /* 抛物线插值*/
            q = (x - v) * (fx - fw);
            p = (x - v) * q - (x - w) * r;
            q = 2.0 * (q - r);

            if (q > 0.0) {
                p = -p;
            }

            q = fabs(q);                                /* 新近似点不满足两个条件*/

            if (fabs(r) > fabs(0.5 * q * d0) || p >= q * (c - x) || p <= q * (a - x)) {
                d0 = (x > xm) ? a - x : c - x;          /* 用黄金分割法*/
                d = G2 * d0;
            } else {
                d0 = d;
                d = p / q;
                u = x + d;

                if (u - a < eps2 ||
                    c - u < eps2) {      /* 抛物线插值结果与端点过于接近，不接受*/
                    d = fabs(eps1) * ((xm - x > 0) ? 1.0 : -1.0);
                }
            }
        }

        if (fabs(d) >= eps1) {
            u = x + d;
        } else {
            u = x + fabs(eps1) * ((d > 0) ? 1.0 : -1.0);
        }

        fu = (*f)(u);

        if (fu <= fx) {                                  /* u比x要好*/
            if (u < x) {                                 /* 最优点u在a和c之间*/
                c = x;
            } else {
                a = x;
            }

            v = w;                                       /* v是上一次的w*/
            w = x;                                       /* w是次优点*/
            x = u;                                       /* x是最优点*/
            fv = fw;
            fw = fx;
            fx = fu;
        } else {                                         /* x比u好*/
            if (u >= x) {                                /* 最优点x在a和c之间*/
                c = u;
            } else {
                a = u;
            }

            if (fu <= fw || w == x) {                    /* u是次优点，赋给w*/
                v = w;
                w = u;
                fv = fw;
                fw = fu;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
            }
        }
    }

    printf("exceed max iterations\n");                   /* 超过迭代次数*/
    *xopt = x;
    return (fx);
}
