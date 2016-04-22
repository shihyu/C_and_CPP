/*======================================================
//函数名：gradroot
//功能描述：求非线性方程组的一组实根
//输入参数：*x0（指向迭代初值和终值的指针）
//          n（方程组个数）
//          f（目标函数的计算与偏导数的计算）
//          eps（精度要求）
//          max（最大迭代次数）
//返回值：0（迭代失败），1（迭代成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int gradroot(x0, n, f, eps, max)
double* x0, (*f)(), eps;
int n, max;
{
    double F, *FD, D, lam;
    int i, num = 0;
    FD = (double*)malloc(sizeof(double) * n); /* 分配空间并检测是否成功*/

    if (FD == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {
        num++;
        F = f(x0, FD);                      /* 计算目标函数和偏导数*/

        if (F > eps) {
            D = 0;

            for (i = 0; i < n; i++) {
                D = D + FD[i] * FD[i];    /* 计算D和系数lamda*/
            }

            lam = F / D;

            for (i = 0; i < n; i++) {
                x0[i] = x0[i] - lam * FD[i];    /* 新值*/
            }
        }

        else {
            return (1);
        }
    } while (num < max);

    if (num == max) {
        return (0);    /* 迭代失败*/
    } else {
        return (1);    /* 迭代成功*/
    }
}


