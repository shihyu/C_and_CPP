#include "stdio.h"
#include "errf.c"
main()
{
    int i, j;
    double x, t;

    for (i = 0; i < 10; i++) {                      /* 共有10行*/
        for (j = 0; j < 3; j++) {                     /* 每行3个*/
            x = 0.1 * (3.0 * i + j);                    /* 计算x*/
            t = errf(x);                                /* 调用误差函数计算*/
            printf("erf(%2.1f)=%e ", x, t);             /* 打印结果*/
        }

        printf("\n");
    }

    getchar();
}
