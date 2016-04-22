/*======================================================
//函数名：ftest.c
//功能描述：用f分布检验两个分布的方差是否有显著性差异
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

int ftest(a, na, b, nb, alpha)
double* a, *b, alpha;
int na, nb;
{
    int  j = 0;
    double meana = 0, meanb = 0, vara = 0, varb = 0; //初始化
    double f, v1, v2, q1;
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
        vara += (a[j] - meana) * (a[j] - meana);    //样本一的方差
    }

    for (j = 0; j < nb; j++) {
        varb += (b[j] - meanb) * (b[j] - meanb);    //样本二的方差
    }

    vara = vara / (na - 1);
    varb = varb / (nb - 1);
    v1 = na - 1;
    v2 = nb - 1;

    if (vara < varb) {                     /* 选择大的一个做分母*/
        f = vara / varb;
        v1 = na - 1;
        v2 = nb - 1;
    } else {
        f = varb / vara;
        v1 = nb - 1;
        v2 = na - 1;
    }

    q1 = 2.0 * beta2(0.5 * v2, 0.5 * v1,
                     v2 / (v2 + v1 * f)); /* 调用不完全贝塔函数计算*/

    if (q1 > 1.0) {
        q1 = 2.0 - q1;
    }

    return (q1 <= alpha);
}

