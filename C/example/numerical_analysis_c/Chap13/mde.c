/*======================================================
//函数名：mde.c
//功能描述：求分布的距
//输入参数：a（简单随机样本的样本值）
//      n（样本个数）
//          mean（存放均值）
//      adev（存放平均差）
//      sddev（存放标准差）
//      var（存放方差）
//      skew（存放斜差）
//      kurt（存放峰态）
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void mde(a, n, mean, adev, sddev, var, skew, kurt)
double* a, *mean, *adev, *sddev, *var, *skew, *kurt;
int n;
{
    int j = 0;
    double* dis;
    dis = (double*)malloc(sizeof(double) * n); //存放数据与均值的差
    *mean = 0;
    *adev = 0;
    *sddev = 0;
    *var = 0;
    *skew = 0;
    *kurt = 0; //初始化

    for (j = 0; j < n; j++) {
        *mean += a[j];
    }

    *mean = *mean / n; //计算均值

    for (j = 0; j < n; j++) {
        dis[j] = a[j] - *mean;
    }

    for (j = 0; j < n; j++) {
        *adev += fabs(dis[j]); //平均差
        *var += dis[j] * dis[j]; //方差
    }

    *adev = *adev / n;
    *var = *var / (n - 1);
    *sddev = sqrt(*var); //标准差

    for (j = 0; j < n; j++) {
        dis[j] = dis[j] / (*sddev);
        *skew += dis[j] * dis[j] * dis[j]; //斜差
        *kurt += dis[j] * dis[j] * dis[j] * dis[j]; //峰态
    }

    *skew = *skew / n;
    *kurt = *kurt / n - 3;
}