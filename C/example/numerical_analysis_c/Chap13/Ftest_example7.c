#include "stdio.h"
#include "stdlib.h"
#include "ftest.c"
#define pi 3.1415926

void main()
{
    int j, na, nb, nc, rtab, rtbc, rtac;
    double* a, *b, *c;
    double x, alpha;
    na = 50;       /* 生成10个随机数*/
    nb = 70;
    nc = 60;
    alpha = 0.1;

    a = (double*)malloc(sizeof(double) * na);
    b = (double*)malloc(sizeof(double) * nb);
    c = (double*)malloc(sizeof(double) * nc);

    if (a == NULL || b == NULL || c == NULL) {
        printf("memory alloc failed.\n");
        exit(0);
    }

    for (j = 0; j < na; j++) {      //随机数样本a
        x = pi * j / na;
        a[j] = sin(x);
    }

    for (j = 0; j < nb; j++) {     //随机样本b
        x = pi * j / nb;
        b[j] = cos(x);
    }

    for (j = 0; j < nc; j++) {     //随机样本c
        x = pi * j / nc;
        c[j] = sin(x);
    }

    rtab = ftest(a, na, b, nb, alpha);   /* 检验a和b*/

    if (rtab) {
        printf("a与b有显著性差异\n");
    } else {
        printf("a与b没有显著性差异\n");
    }


    rtbc = ftest(c, nc, b, nb, alpha);   /* 检验b和c*/

    if (rtbc) {
        printf("b与c有显著性差异\n");
    } else {
        printf("b与c没有显著性差异\n");
    }

    rtac = ftest(a, na, c, nc, alpha);  /* 检验a和c*/

    if (rtac) {
        printf("a与c有显著性差异\n");
    } else {
        printf("a与c没有显著性差异\n");
    }

}
