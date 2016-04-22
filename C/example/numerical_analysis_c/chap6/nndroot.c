/*======================================================
//函数名：nndroot
//功能描述：求非线性方程组的一组实根
//输入参数：*x0（指向迭代初值和终值的指针），
//           n（方程组个数），f（ 非线性方程的计算）
//           eps（精度要求），max（最大迭代次数）
//           h（差商中的微小变量），t（放缩系数）
//返回值：0（迭代失败），1（迭代成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include"r_gaus.c"

int nndroot(x0, n, f, eps, max, h, t)
double* x0, eps, h, t;
void (*f)();
int n, max;
{
    double* f0, *fi, *fx, *dl, dis, sum;
    int i, num = 0;
    f0 = (double*)malloc(sizeof(double) * n);
    fx = (double*)malloc(sizeof(double) * n);
    fi = (double*)malloc(sizeof(double) * n * n);
    dl = (double*)malloc(sizeof(double) * n);

    if (f0 == NULL || fx == NULL || fi == NULL || dl == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {
        num++;
        f(x0, f0, fi, h);                     /* 计算方程组值以及偏移h后的值*/

        dis = 0;

        for (i = 0; i < n; i++) {
            if (fabs(f0[i]) > dis) {
                dis = fabs(f0[i]);    /* 计算max方程的值*/
            }
        }

        if (dis > eps) {                      /* 不满足精度，继续迭代*/
            if (r_gaus(fi, f0, fx, n, 1e-8) == 0) { /* 调用高斯消去法，解线性方程组*/
                return (0);
            } else {
                sum = 0;

                for (i = 0; i < n; i++) {
                    sum = fx[i] + sum;
                }

                sum = h / (1 - sum);

                for (i = 0; i < n; i++) {
                    dl[i] = fx[i] * sum;      /* 差值*/
                    x0[i] = x0[i] - dl[i];    /* 新值*/
                }

                h = h * t;
            }
        } else {
            return (1);
        }
    } while (num < max);

    free(f0);
    free(fi);
    free(dl);

    if (num == max) {
        return (0);    /* 迭代失败*/
    } else {
        return (1);    /* 迭代成功*/
    }
}
