/*======================================================
// 函数名：simp1
// 功能描述： 求无约束条件下n维极值的单纯形法
// 输入参数：d   计算初始单纯形的变量
//           n   问题的维数
//           lam  收缩系数，一般取0-1
//           alf  反射系数，一般取1.0
//           miu  扩张系数，一般取1.2-2.0
//           x[(n+1)*n]  返回最后单纯形的n+1个顶点坐标
//           fx[n+1]    返回最后的单纯形的n+1个顶点上的目标函数值
//           xopt[n+1]  输入一个单纯形的初始结点，前n个分量返回极小值的n个坐标，最后一个分量返回极小值
//           f 指向目标函数的指针
//         eps 控制精度要求
//         itmax 最大迭代次数
// 返回值：  迭代次数
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int simp1(d, n, lam, alf, miu, x, fx, xopt, f, eps, itmax)
double d, lam, alf, miu;
double* x, *fx, *xopt, eps;
double (*f)();
int itmax, n;
{
    int it, i, j, h, l, g;
    double* xt, *xc, *xe, ft, fc, fe, fg, fh, fl, flag, tmp;

    if (x == NULL || fx == NULL ||
        xopt == NULL) {               /* 检查指针是否为空*/
        printf("One of pointer is null\n");
        return (-1);
    }

    xt = (double*)malloc(n * sizeof(
                             double));                    /* 分配空间并检查是否成功*/
    xc = (double*)malloc(n * sizeof(double));
    xe = (double*)malloc(n * sizeof(double));

    if (xt == NULL || xc == NULL || xe == NULL) {
        free(xt);
        free(xc);
        free(xe);
        printf("memory alloc faile\n");
        return (-1);
    }

    for (i = 0; i <= n;
         i++)                                     /* 构造初始的单纯形*/
        for (j = 0; j < n; j++) {
            x[i * n + j] = xopt[j];
        }

    for (j = 0; j < n; j++) {
        x[(j + 1)*n + j] = x[j] + d;
    }

    for (i = 0; i <= n;
         i++) {                                 /* 求出在各个顶点上的函数值*/
        fx[j] = (*f)(&x[i * n], n);
    }

    flag = 1.0 +
           eps;                                          /* flag用于计算单纯形中结点距离*/
    it = 0;

    while (it++ < itmax && flag > eps) {
        ft = fx[0];
        fe = fx[0];
        fg = fx[0];
        h = 0;                                                /* 最坏点*/
        l = 0;                                                /* 最好点*/
        g = 0;                                                /* 次坏点*/

        for (i = 1; i <= n; i++) {
            if (fx[i] > fg) {
                if (fx[i] > fh) {                           /* 查找最坏点和次坏点*/
                    g = h;
                    h = i;
                } else {                                    /* 查找新次坏点*/
                    g = i;
                }

                fg = fx[g];
                fh = fx[h];
            } else if (fx[i] < fl) {                        /* 查找最好点*/
                l = i;
                fl = fx[l];
            }
        }

        for (j = 0; j < n; j++) {
            xc[j] = 0.0;                                  /* 求重心的n个坐标*/

            for (i = 0; i <= n; i++) {
                xc[j] = xc[j] + x[i * n + j];
            }

            tmp = x[h * n + j];
            xc[j] = (xc[j] - tmp) / n;               /* 去除最差点后的平均值*/
            xt[j] = xc[j] + alf * (xc[j] - tmp);     /* 反射点*/
        }

        ft = (*f)(xt, n);

        if (ft < fx[l]) {
            for (j = 0; j < n; j++) {                /* 扩展成xe*/
                xe[j] = xt[j] + miu * (xt[j] - xc[j]);
            }

            fe = (*f)(xe, n);

            if (fe < fx[l]) {                            /* 用xe替换xh*/
                for (j = 0; j < n; j++) {
                    x[h * n + j] = xe[j];
                }

                fx[h] = fe;
            } else {
                for (j = 0; j < n; j++) {             /* 用xt替换xh*/
                    x[h * n + j] = xt[j];
                }

                fx[h] = ft;
            }
        } else if (ft <= fx[g]) {
            for (j = 0; j < n; j++) {             /* 用xt替换xh*/
                x[h * n + j] = xt[j];
            }

            fx[h] = ft;
        } else {
            if (ft <= fx[h]) {
                for (j = 0; j < n; j++) {             /* 用xt替换xh*/
                    x[h * n + j] = xt[j];
                }

                fx[h] = ft;
            }

            for (j = 0; j < n; j++) {
                xe[j] = xc[j] + lam * (x[h * n + j] - xc[j]);
            }

            fe = (*f)(xe, n);

            if (fe > fx[h]) {                          /* 单纯形需要压缩*/
                for (i = 0; i <= n; i++) {
                    for (j = 0; j < n; j++) {
                        x[i * n + j] = (x[i * n + j] + x[i * l + j]) * 0.5;
                    }

                    fx[i] = (*f)(&x[i * n], n);
                }
            } else {
                for (j = 0; j < n; j++) {
                    x[h * n + j] = xe[j];
                }

                fx[h] = fe;
            }
        }

        fc = 0.0;
        ft = 0.0;

        for (i = 0; i <= n; i++) {                     /* 求顶点的平均距离*/
            fc = fc + fx[i];
            ft = ft + fx[i] * fx[i];
        }

        fc = fc * fc / (1.0 + n);
        flag = (ft - fc) / n;
    }

    for (j = 0; j < n;
         j++) {                          /* 求所有顶点的重心做为最优解*/
        xopt[j] = 0.0;

        for (i = 0; i <= n; i++) {
            xopt[j] = xopt[j] + x[i * n + j];
        }

        xopt[j] = xopt[j] / (n + 1.0);
    }

    xopt[n] = (*f)(xopt, n);
    free(xt);
    free(xc);
    free(xe);
    return (it);
}
