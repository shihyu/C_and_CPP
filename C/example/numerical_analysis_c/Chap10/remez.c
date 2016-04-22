/*======================================================
// 函数名：remez
// 功能描述：最佳一致逼近的里米兹算法
// 输入参数：a 区间左端点
//           b 区间右端点
//           n 逼近多项式的次数加1
//           p 指向返回n个多项式系数数组的指针
//           f 指向被逼近的函数的指针
//           eps 精度要求，一般在1e-7以下
//           itmax 最大迭代次数
// 返回值：  整型。若拟合成功则返回1,否则返回0
=========================================================*/

#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "r_gaus.c"

void remez(a, b, n, p, f, itmax, eps)
double a, b, *p, (*f)(), eps;
int n, itmax;
{
    int i, j, k, n1, m,
        kk;         /* i,j二维数组的行列，k一维数组元素号，m新值插入点*/
    double h, x1, newx, s, t;       /* 用于搜索偏差最大点*/
    double* x, *ff, *A, *temp, *tempf;
    n1 = n + 1;                     /* 方程组的阶数*/
    x = (double*)malloc(n1 * sizeof(double));
    ff = (double*)malloc(n1 * sizeof(double));
    A = (double*)malloc(n1 * n1 * sizeof(double));
    temp = (double*)malloc(n1 * n1 * sizeof(double));
    tempf = (double*)malloc(n1 * sizeof(double));

    for (k = 0; k < n1;
         k++) {    /* 在区间内取n+1次切比雪夫多项式的交错点组做为初始点集*/
        t = cos((n - k) * 3.1415926 / (1.0 * n));
        t = (b + a + (b - a) * t) / 2.0;
        x[k] = t;
    }

    double pre_mu = 1.0e35;                /* 保证迭代能够进行*/
    double mu = 1.0;

    for (i = 0; i < n1; i++) {
        ff[i] = (*f)(x[i]);
        xx[i * n1] = 1.0;

        for (j = 1; j < n; j++) {
            xx[i * n1 + j] = x[i] * xx[i * n1 + j - 1];
        }

        xx[i * n1 + n] = mu;
        mu = -mu;
    }                                      /* 初始X矩阵构造*/

    /* 下面开始迭代*/
    int flagx;
    int times = 0;                         /* 记录迭代次数*/

    while (times < itmax && fabs(pre_mu - mu) < eps) {
        for (i = 0; i < n1; i++) {        /* 复制一份，因为调用的函数会破坏数据*/
            tempf[i] = ff[i];

            for (j = 0; j < n1; j++) {
                temp[i * n1 + j] = xx[i * n1 + j];
            }
        }

        r_gaus(temp, tempf, p, n, 1e-10); /* 解出系数和偏差*/
        pre_mu = mu;
        mu = fabs(p[n]);
        x1 = a;
        newx = a;                         /* newx记录新找到的最大偏差点*/
        h = 0.1 * (b - a) / (1.0 * n);

        while (x1 < b) {                  /* 扫描寻找最大偏差点newx*/
            s = (*f)(x1);
            t = p[n - 1];

            for (i = n - 2; i >= 0; i--) {
                t = t * x1 + p[i];
            }

            if (fabs(s - t) > mu) {
                flagx = (s - t) > 0 ? 1 : -1;
                mu = fabs(s - t);
                newx = x1;
            }

            x1 = x1 + h;
        }

        for (i = 0; i < n1; i++)          /* 扫描寻找最大偏差点应处的位置m*/
            if (newx > x[i]) {
                m = i;
            }

        if (newx <
            x[0]) {               /* 分情况替换，同时更改系数矩阵xx和存放函数值的结果向量ff*/
            kk = 0;                      /* 记录下待修改的行号*/
            s = (*f)(x[0]);
            t = p[n - 1];

            for (i = n - 2; i >= 0; i--) {
                t = t * x[0] + p[i];
            }

            s = s - t;

            if (s * flagx < 0.0) {       /* 异号，添加到最前*/
                for (k = n - 1; k >= 0; k--) {
                    ff[k + 1] = ff[k];
                    x[k + 1] = x[k];
                }

                double* tempxx = xx[n];

                for (i = n; i > 0; i--) {
                    xx[i] = xx[i - 1];
                }

                xx[0] = tempxx;
            }
        } else if (newx > x[6]) {
            kk = 6;                      /* 记录下待修改的行号*/
            s = (*f)(x[6]);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x[6] + p[i];
            }

            s = s - t;

            if (s * flagx < 0.0) {       /* 异号，添加到最后*/
                for (k = 0; k < 6; k++) {
                    ff[k] = ff[k + 1];
                    x[k] = x[k + 1];
                }

                double* tempxx = xx[0];

                for (i = 0; i < 6; i++) {
                    xx[i] = xx[i + 1];
                }

                xx[6] = tempxx;
            }
        } else {                          /* 最大值在x[m]与x[m+1]之间*/
            s = (*f)(x[m]);
            t = p[5];

            for (i = 4; i >= 0; i--) {
                t = t * x[m] + p[i];
            }

            s = s - t;

            if (s * flagx > 0.0) {        /* 同号，则替换x[m]*/
                kk = m;                   /* 记录下待修改的行号*/
                xx[kk][6] = -xx[kk + 1][6];
            } else {                       /* 异号，则替换x[m+1]*/
                kk = m + 1;                /* 记录下待修改的行号*/
                xx[kk][6] = -xx[m][6];
            }
        }

        x[kk] = newx;
        ff[kk] = (*f)(x[kk]);

        for (j = 1; j < 6; j++) {
            xx[kk][j] = x[kk] * xx[kk][j - 1];
        }

        times++;
    }

    free(x);
    free(ff);
    free(A);
    free(Xemp);
    free(tempf);
}
