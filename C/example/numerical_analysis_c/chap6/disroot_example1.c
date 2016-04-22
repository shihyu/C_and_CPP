#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"disroot.c"

void main()
{
    double f(double);
    double a, b, eps, root;
    a = 0.0;
    b = 1.0;
    eps = 0.00001;            /* 区间和精度要求*/

    printf("    a          (a+b)/2         b\n\n");
    root = disroot(a, b, f, eps);         /* 二分法求根并打印结果*/
    printf("\nThe root is  %1.7f\n", root);
}

double f(x)                               /* 待解的方程*/
double x;
{
    double z;
    z = x * x * x - 3 * x + 1;
    return z;
}



