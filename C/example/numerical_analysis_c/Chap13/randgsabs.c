/*======================================================
//函数名：randgsabs
//功能描述：生成L个N~(a,b)分布的随机数
//输入参数：L(序列个数) a(正态分布的均值) b(正态分布的方差)，G(指向生成随机数的指针)
//返回值：1:生成成功。0：生成失败
=========================================================*/
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#define PI 3.14159

double randgsabs(L, a, b, G)
int L;
double a, b;
double* G;
{
    int i;
    double U1, U2;
    srand((unsigned)time(0));/*用系统时钟做种子*/

    for (i = 0; i < L; i = i + 2) {
        U1 = rand() / (double)RAND_MAX; /*生成(0,1)随机数U1*/
        U2 = rand() / (double)RAND_MAX; /*生成(0,1)随机数U2*/
        G[i] = sqrt(-2 * log(U1)) * sin(2 * PI * U2); /*生成标准正态分布随机数G1*/
        G[i] = sqrt(b) * G[i] + a; /*生成服从N~(a,b)的随机数G1*/
        G[i + 1] = sqrt(-2 * log(U1)) * cos(2 * PI * U2); /*生成标准正态分布随机数G2*/
        G[i + 1] = sqrt(b) * G[i + 1] + a; /*生成服从N~(a,b)的随机数G2*/
    }

    return (1);
}

