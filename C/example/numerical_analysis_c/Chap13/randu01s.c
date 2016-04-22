/*======================================================
//函数名：randu01s
//功能描述：生成(0,1)区间的均匀分布的随机序列
//输入参数：L(生成随机序列的长度) u_ran(指向生成随机数序列的指针)
//返回值：1：成功生成。0：生成失败。
=========================================================*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int randu01s(L, u_ran)
int L;
double* u_ran;
{
    int i;
    srand((unsigned)time(0));             /* 用系统时钟做种子*/

    for (i = 0; i < L; i++) {
        u_ran[i] = rand() / (double)RAND_MAX;    /* 生成(0,1)随机数，L次 */
    }

    return (1);
}

