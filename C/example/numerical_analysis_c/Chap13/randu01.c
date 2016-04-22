/*======================================================
//函数名：randu01
//功能描述：生成一个(0,1)区间的均匀分布的随机数
//输入参数：无
//返回值：一个(0,1)区间内的均匀分布随机数
=========================================================*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
double randu01(x0)
int x0;
{
    double u_ran;
    srand((unsigned)time(0));             /* 用系统时钟做种子*/
    u_ran = rand() / (double)RAND_MAX;    /* 生成(0,1)随机数*/
    return (u_ran);
}
