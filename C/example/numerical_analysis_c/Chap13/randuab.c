/*=============================================================
//函数名：randuab
//功能描述：生成一个[a,b]区间的均匀分布的随机整数数
//输入参数：a ，b(区间范围)
//返回值：一个[a,b]区间内的均匀分布随机整数
=========================================================*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
double randuab(a, b)
int a, b;
{
    double u_ran;
    int u_ran
    srand((unsigned)time(0));            /* 用系统时钟做种子*/
    u_ran = rand() / (double)RAND_MAX;   /* 生成(0,1)随机数*/
    uab_ran = (int)((b - a + 1) * u_ran) + a;
    return (uab_ran);
}

