/*======================================================
//函数名：ttest.c
//功能描述：用t分布检验两个分布的均值是否有显著性差异(方差相同)
//输入参数：a（简单随机样本一的样本值）
//      na（样本一的个数）
//          b（简单随机样本二的样本值）
//      nb（样本二的个数）
//      alpha（显著性标准）
//返回值：1（显著），0（不显著）
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "beta2.c"

int ttest(a, na, b, nb, alpha)
double* a, *b, alpha;
int na, nb;
{
    int  j = 0;
    double meana = 0, meanb = 0, vara = 0, varb = 0; //初始化
    double sd, t, x, p;
    int v;
    double eps = 0.00001;

    for (j = 0; j < na; j++) {
        meana += a[j];
    }

    meana = meana / na;                     //计算样本一均值

    for (j = 0; j < nb; j++) {
        meanb += b[j];
    }

    meanb = meanb / nb;                     //计算样本二均值

    for (j = 0; j < na; j++) {
        vara += (a[j] - meana) * (a[j] - meana);    //样本一的方差*na
    }

    for (j = 0; j < nb; j++) {
        varb += (b[j] - meanb) * (b[j] - meanb);    //样本二的方差*nb
    }

    v = na + nb - 2;
    sd = sqrt((1.0 / na + 1.0 / nb) / (double)v * (vara + varb)); //计算sd
    t = (meana - meanb) / sd;               //计算t
    x = v / (v + t * t);
    p = beta2(v / 2, 0.5, x, eps);          //求概率
    return (p <= alpha);
}



