#include "stdio.h"
#include "rpmva.c"
#include "rpva.c"
main()
{
    int i;
    double y[6], tmp;
    static double a[7] = {7.0, -7.0, 1.0, 3.0, -5.0, 2.0, 2.0};
    static double x[6] = {1.0, 1.1, 0.3, -0.3, -1.1, -1.9};
    rpmva(a, 7, x, 6, y); /* 调用一次求多个值的函数，并打印结果*/
    printf("rpmva:\n");

    for (i = 0; i < 6; i++) {
        printf("x(%d)=%2.5f; y(%d)=%2.5f\n", i, x[i], i, y[i]);
    }

    printf("\n");
    printf("rpva:\n");    /* 循环调用一次求一个值的函数，并打印结果。*/

    for (i = 0; i < 6; i++) {
        tmp = rpva(a, 7, x[i]);
        printf("x(%d)=%2.5f; y(%d)=%2.5f\n", i, x[i], i, tmp);
    }

    printf("\n");
}

