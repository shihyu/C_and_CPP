/*======================================================
//函数名：randuabs
//功能描述：生成[a,b]区间的均匀分布的随机整数序列
//输入参数：L(生成随机序列的长度)，a，b（区间范围）,uab_ran(指向生成随机数序列的指针)
//返回值：1：成功生成。0：生成失败
=========================================================*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int randuabs(L, a, b, uab_ran)
int L, a, b;
int* uab_ran;
{
    int i;
    double* u_ran;
    u_ran = (double*)malloc(L * sizeof(double));

    if (u_ran == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    srand((unsigned)time(0));                     /* 用系统时钟做种子*/

    for (i = 0; i < L; i++) {
        u_ran[i] = rand() / (double)RAND_MAX;     /* 生成(0,1)随机数，L次*/
        uab_ran[i] = (int)(u_ran[i] * (b - a + 1)) + a;
    }

    return (1);
}

