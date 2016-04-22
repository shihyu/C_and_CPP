/*======================================================
// 函数名：dbrent
// 功能描述：使用一阶导数的Brent算法法求极值
// 输入参数：a 初始区间的左端点
//           b 初始区间的中间点
//           c 初始区间的右端点
//           f 函数指针
//           df 函数的一阶导数的指针
//           xopt 指针，指向极值点的坐标
//           eps 精度限度
//           itmax 最大迭代次数
// 返回值：  函数的极小值
=========================================================*/

#include "stdio.h"
#include "math.h"

double dbrent(a, b, c, f, df, xopt, eps, itmax)
double a, b, c, eps;
double (*f)(double), (*df)(double);
double* xopt;
int itmax;
{
    int it, t1, t2;                                    /* 用于判断接受d1还是d2*/
    double xm, x, u, w, v, fx, fu, fw, fv, du, dv, dw, dx;
    double u1, u2, eps1, eps2, d0, d, d1, d2;

    x = w = v = b;                                     /*x,w,v的初值为b*/
    fx = fw = fv = (*f)(b);
    dx = dw = dv = (*df)(b);
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
            d0 = (dx > 0.0) ? a - x : c - x;            /* 向导数小于零的方向二分*/
            d = 0.5 * d0;
        } else {
            d2 = d1 = 2.0 * (c - a);

            if (dw != dx) {                             /* 依据w,x计算近似最优点与x的距离d1*/
                d1 = (w - x) / (dx - dw) * dx;
            }

            if (dv != dx) {                             /* 依据v,x计算近似最优点与x的距离d2*/
                d2 = (v - x) / (dx - dv) * dx;
            }

            u1 = x + d1;                                /* 依据w,x得到的近似最优点*/
            u2 = x + d2;                                /* 依据v,x得到的近似最优点*/
            t1 = (a - u1) * (c - u1) < 0.0 &&
                 d1 * dx <= 0; /* u1在a和c之间，且是导数小于零的方向*/
            t2 = (a - u2) * (c - u2) < 0.0 &&
                 d2 * dx <= 0; /* u1在a和c之间，且是导数小于零的方向*/

            if (t1 || t2) {                             /* 选择接受u1或u2*/
                if (t1 && t2) {
                    d = (fabs(d1) < fabs(d2)) ? d1 : d2;    /* 两个都可，则选择较小的一个*/
                } else if (t1) {
                    d = d1;
                } else {
                    d = d2;
                }

                if (fabs(d) >= fabs(0.5 * d0)) {
                    d0 = (dx > 0.0) ? a - x : c - x;    /* 向导数小于零的方向二分*/
                    d = 0.5 * d0;
                } else {                                /* d小于上次步长的一半，才接受*/
                    u = x + d;

                    if (u - a < eps2 || c - u < eps2) { /* 过于接近，则不接受，直接对x进行微调*/
                        d = fabs(eps1) * ((xm - x > 0) ? 1.0 : -1.0);
                    }
                }
            } else {                                    /* u1和u2都不能接受时，二分*/
                d0 = (dx > 0.0) ? a - x : c - x;        /* 向导数小于零的方向二分*/
                d = 0.5 * d0;
            }
        }

        if (fabs(d) >= eps1) {
            u = x + d;
        } else {
            u = x + fabs(eps1) * ((d > 0) ? 1.0 : -1.0); /* 最小的步长*/
            fu = (*f)(u);

            if (fu > fx) {                         /* 沿下降方向进行最小的步长仍然增加，则说明已经找到了最优点*/
                *xopt = x;
                return (fx);
            }
        }

        fu = (*f)(u);
        du = (*df)(u);

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
            dv = dw;
            dw = dx;
            dx = du;
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
                dv = dw;
                dw = du;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
                dv = du;
            }
        }
    }

    printf("exceed max iterations\n");                   /* 超过迭代次数*/
    *xopt = x;
    return (fx);
}
