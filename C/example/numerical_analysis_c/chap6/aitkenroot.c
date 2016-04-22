/*======================================================
//函数名：aitkenroot
//功能描述：求出[a,b]区间内的非线性方程f(x)的一个实根
//输入参数：*x0（指向迭代初值和终值的指针）
//          f（迭代函数）
//          eps（精度要求）
//          max（最大迭代次数）
//返回值：0（迭代失败），1（迭代成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int aitkenroot(x0, f, eps, max)
double* x0, (*f)(), eps;
int max;
{

    double x, x1, x2, dis;
    int num = 0;

    do {
        x1 = f(*x0);                     /* 第一次简单迭代*/
        x2 = f(x1);                      /* 第二次简单迭代*/
        dis = fabs(x2 - x1);             /* 判断距离*/
        x = x2 - dis * dis / (x2 - 2 * x1 + *x0); /* 计算新的值*/
        num++;
        printf("%1.7f    %1.7f    %1.7f\n", *x0, x, dis);
        *x0 = x;
    } while (dis > eps &&
             num < max);     /* 测试是否满足精度要求，不满足则继续迭代*/

    if (num == max) {
        return (0);    /* 迭代失败*/
    } else {
        return (1);    /* 迭代成功*/
    }

}

