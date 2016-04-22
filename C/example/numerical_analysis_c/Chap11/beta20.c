#include "stdio.h"
#include "beta2.c"
main()
{
    int i, j, k;
    double x, a0, b0, y;
    double e1 = 1.0e-7;
    double a[5] = {0.5, 0.5, 5.0};
    double b[5] = {0.5, 5.0, 0.5};

    for (i = 0; i < 3; i++) {
        a0 = a[i];
        b0 = b[i];
        printf("a = %2.1f,b=%2.1f\n", a0, b0);       /* 打印a和b*/

        for (j = 0; j < 5; j++) {                    /* 打印5行*/
            for (k = 0; k < 2; k++) {                  /* 每行两列*/
                x = 0.1 * (2 * j + k);                   /* x在0.0-0.9之间，共10个*/
                y = beta2(a0, b0, x, e1);                /* 调用函数计算*/
                printf("B(x=%2.1f)=%e ", x, y);          /* 打印结果*/
            }

            printf("\n");
        }

        printf("\n");
    }

    printf("\n");
    getchar();
}

