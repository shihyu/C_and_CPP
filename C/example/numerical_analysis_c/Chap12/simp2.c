/*======================================================
// 函数名：simp2
// 功能描述： 求约束条件下n维极值的单纯形法
// 输入参数：n   问题的维数
//           m   函数约束条件的个数
//           a[n] 常量约束条件中x的下界
//           b[n] 常量约束条件中x的上界
//           (*sf)() 计算顶点是否满足函数约束条件的函数
//           d    计算初始单纯形的参数
//           alf  反射系数，一般取1.3
//           x[(2n)*n]  返回最后单纯形的2n个顶点坐标
//           fx[2n]    返回最后的单纯形的2n个顶点上的目标函数值
//           xopt[n+1]  输入一个单纯形的初始结点，前n个分量返回极小值的n个坐标，最后一个分量返回极小值
//           f 指向目标函数的指针
//         eps 控制精度要求
//         itmax 最大迭代次数
// 返回值：  迭代次数
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define TINY 1.0e-7

int simp2(n, m, a, b, d, alf, eps, x, fx, xopt, sf, f, itmax)
int itmax, n, m;
double* a, *b, *x, *fx, *xopt;
double d, alf, eps;
double (*f)();
int (*sf)();
{
    int it, in, i, j, h, g, iflag;
    double* xt, *xc, ft, fc, fg, fh, flag, tmp, rr, simprn();

    if (a == NULL || b == NULL || x == NULL || fx == NULL ||
        xopt == NULL) {         /* 检查指针是否为空*/
        printf("One of pointer is null\n");
        return (-1);
    }

    xt = (double*)malloc(n * sizeof(
                             double));                    /* 分配空间并检查是否成功*/
    xc = (double*)malloc(n * sizeof(double));

    if (xt == NULL || xc == NULL) {
        free(xt);
        free(xc);
        printf("memory alloc faile\n");
        return (-1);
    }

    j = 0;

    while (j <
           n)                                             /* 检查初始点是否满足约束*/
        if (a[j] <= xopt[j] && xopt[j] <= b[j]) {
            j++;
        } else {
            free(xt);
            free(xc);
            printf("imput x0 is out of range\n");
            return (0);
        }

    if (!(*sf)(xopt)) {
        free(xt);
        free(xc);
        printf("imput x0 is out of range\n");
        return (0);
    }

    for (j = 0; j < n; j++) {
        x[j] = xopt[j];    /* 初始结点*/
    }

    fx[0] = (*f)(xopt);
    rr = 0.0;

    for (i = 1; i < 2 * n;
         i++)                                 /* 构造初始的单纯形*/
        for (j = 0; j < n; j++) {
            x[i * n + j] = a[j] + d * simprn(&rr);
        }

    for (i = 1; i < 2 * n;
         i++) {                               /* 调整顶点满足函数约束条件*/
        it = 1;
        in = i * n;

        for (j = 0; j < n; j++) {                              /* 求出已知结点的重心*/
            tmp = 0.0;

            for (h = 0; h < i; h++) {
                tmp = tmp + x[h * n + j];
            }

            xc[j] = tmp / (1.0 * i);
        }

        iflag = 0;

        while (it == 1 && iflag < 200) {
            it = 0;

            for (j = 0; j < n; j++) {                       /* 调整使其满足常量约束条件*/
                if (x[in + j] < a[j]) {
                    x[in + j] = a[j] + TINY;
                    it = 1;
                } else if (x[in + j] > b[j]) {
                    x[in + j] = b[j] - TINY;
                    it = 1;
                }
            }

            if (it == 0) {                                /* 调整使其满足函数约束条件*/
                if (!(*sf)(&(x[i * n]))) {
                    for (j = 0; j < n; j++) {
                        x[in + j] = (x[in + j] + xc[j]) * 0.5;
                    }

                    it = 1;
                }
            }

            iflag++;
        }

        if (iflag >= 200) {
            free(xt);
            free(xc);
            printf("simplex construction failed\n");
            return (0);
        }

        fx[i] = (*f)(
                    &x[in]);                                  /* 求出在各个顶点上的函数值*/
    }

    flag = 1.0 +
           eps;                                         /* flag用于计算单纯形中结点距离*/
    it = 0;

    while (it++ < itmax && flag > eps) {
        ft = fx[0];
        fg = fx[0];
        h = 0;                                                /* 最坏点*/
        g = 0;                                                /* 次坏点*/

        for (i = 1; i < 2 * n; i++) {
            if (fx[i] > fg) {
                if (fx[i] > fh) {                           /* 查找最坏点和次坏点*/
                    g = h;
                    h = i;
                } else {                                    /* 查找新次坏点*/
                    g = i;
                }

                fg = fx[g];
                fh = fx[h];
            }
        }

        for (j = 0; j < n; j++) {
            xc[j] = 0.0;                                  /* 求重心的n个坐标*/

            for (i = 0; i < 2 * n; i++) {
                xc[j] = xc[j] + x[i * n + j];
            }

            tmp = x[h * n + j];
            xc[j] = (xc[j] - tmp) / (2 * n - 1.0);        /* 去除最差点后的平均值*/
            xt[j] = xc[j] + alf * (xc[j] - tmp);         /* 反射点*/
        }

        iflag = 1;

        while (iflag == 1) {
            ft = (*f)(xt);

            if (ft > fg) {                                 /* 调整使ft<=fg*/
                for (j = 0; j < n; j++) {
                    xt[j] = (xt[j] + xc[j]) * 0.5;
                }

                ft = (*f)(xt);
            }

            iflag = 0;

            for (j = 0; j < n; j++) {                      /* 调整使其满足常量约束条件*/
                if (xt[j] < a[j]) {
                    xt[j] = a[j] + TINY;
                    iflag = 1;
                } else if (xt[j] > b[j]) {
                    xt[j] = b[j] - TINY;
                    iflag = 1;
                }
            }

            if (iflag == 0) {                               /* 调整使其满足函数约束条件*/
                if (!(*sf)(xt)) {
                    for (j = 0; j < n; j++) {
                        xt[j] = (xt[j] + xc[j]) * 0.5;
                    }

                    iflag = 1;
                }
            }
        }

        for (j = 0; j < n; j++) {                          /* xt=> xh*/
            x[h * n + j] = xt[j];
        }

        fx[h] = ft;
        fc = 0.0;
        ft = 0.0;

        for (i = 0; i < 2 * n; i++) {                   /* 求顶点的平均距离*/
            tmp = fx[i];
            fc = fc + tmp;
            ft = ft + tmp * tmp;
        }

        fc = fc * fc / (2.0 * n);
        flag = (ft - fc) / (2.0 * n - 1.0);
    }

    for (j = 0; j < n;
         j++) {                          /* 求所有顶点的重心做为最优解*/
        xopt[j] = 0.0;

        for (i = 0; i < 2 * n; i++) {
            xopt[j] = xopt[j] + x[i * n + j];
        }

        xopt[j] = xopt[j] / (2.0 * n);
    }

    xopt[n] = (*f)(xopt);
    free(xt);
    free(xc);
    return (it);
}

static double simprn(rr)                               /* 求随机数的子程序*/
double* rr;
{
    int m;
    double s = 65536.0, u = 2053.0, v = 13849.0;
    *rr = v + u * (*rr);
    m = *rr / s;
    *rr = *rr - m * s;
    return (*rr / s);
}