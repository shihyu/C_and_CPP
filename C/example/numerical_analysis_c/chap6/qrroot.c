/*======================================================
//函数名：qrroot
//功能描述：QR方法求多项式方程全部实根
//输入参数：a   指向存放多项式系数的指针（降幂排列）
            n   多项式阶数
            u   返回的根的实部
            v   返回的根的虚部
            eps 精度要求，用于判断元素是否为0
            itmax 最大迭代次数
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "mhdqr.c"

int qrroot(a, n, u, v, eps, itmax)
double* a, *u, *v, eps;
int n, itmax;
{
    int i;
    double* H;
    H = (double*)malloc(sizeof(double) * n * n); /* 生成的上H矩阵*/

    for (i = 0; i < n; i++) {
        H[i] = -1.0 * a[i + 1] / a[0];    /* 第一行*/
    }

    for (i = n; i < n * n; i++) {
        H[i] = 0.0;    /* 下面为0*/
    }

    for (i = 1; i < n; i++) {
        H[i * n + i - 1] = 1.0;    /* 次对角线为1*/
    }

    return (mhdqr(H, n, u, v, eps, itmax));   /* 调用上H矩阵求特征值的函数*/
}



