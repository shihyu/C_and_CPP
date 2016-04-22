#include "stdio.h"
#include "stdlib.h"
#include "ttest.c"
#include "tutest.c"
#define pi 3.1415926

void main()
{
    int j, na, nb, nc, rtab, rtbc, rtac;
    double* a, *b, *c;
    double x, meana, meanb, meanc, vara, varb, varc, alpha;
    na = 50; /*生成100个随机数*/
    nb = 70;
    nc = 60;
    alpha = 0.05;

    a = (double*)malloc(sizeof(double) * na);
    b = (double*)malloc(sizeof(double) * nb);
    c = (double*)malloc(sizeof(double) * nc);

    if (a == NULL || b == NULL || c == NULL) {
        printf("memory alloc failed.\n");
        exit(0);
    }

    for (j = 0; j < na; j++) {      //随机数样本一
        x = pi * j / na;
        a[j] = sin(x);
    }

    for (j = 0; j < nb; j++) {     //随机样本二
        x = pi * j / nb;
        b[j] = cos(x);
    }

    for (j = 0; j < nc; j++) {     //随机样本三
        x = pi * j / nc;
        c[j] = sin(x);
    }

    for (j = 0; j < na; j++) {
        meana += a[j];
    }

    meana = meana / na;                     //计算样本一均值

    for (j = 0; j < nb; j++) {
        meanb += b[j];
    }

    meanb = meanb / nb;                     //计算样本二均值

    for (j = 0; j < nc; j++) {
        meanc += c[j];
    }

    meanc = meanc / nc;                     //计算样本三均值

    for (j = 0; j < na; j++) {
        vara += (a[j] - meana) * (a[j] - meana);
    }

    vara = vara / (na - 1);                 //样本一的方差

    for (j = 0; j < nb; j++) {
        varb += (b[j] - meanb) * (b[j] - meanb);
    }

    varb = varb / (nb - 1);                 //样本二的方差

    for (j = 0; j < nc; j++) {
        varc += (c[j] - meanc) * (c[j] - meanc);
    }

    varc = varc / (nc - 1);                 //样本三的方差

    if (vara == varb) {   //方差相同时调用ttest
        rtab = ttest(a, na, b, nb, alpha);
    } else {
        rtab = tutest(a, na, b, nb, alpha);    //方程不同时调用tutest
    }

    if (rtab) {
        printf("a与b有显著性差异\n");
    } else {
        printf("a与b没有显著性差异\n");
    }

    if (varc == varb) {
        rtbc = ttest(c, nc, b, nb, alpha);
    } else {
        rtbc = tutest(c, nc, b, nb, alpha);
    }

    if (rtbc) {
        printf("b与c有显著性差异\n");
    } else {
        printf("b与c没有显著性差异\n");
    }

    if (vara == varc) {
        rtac = ttest(a, na, c, nc, alpha);
    } else {
        rtac = tutest(a, na, c, nc, alpha);
    }

    if (rtac) {
        printf("a与c有显著性差异\n");
    } else {
        printf("a与c没有显著性差异\n");
    }

}
