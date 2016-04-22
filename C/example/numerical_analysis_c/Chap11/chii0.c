#include "stdio.h"
#include "chii.c"
main()
{
    int i, n;
    double x, y;

    for (i = 1; i < 5; i++) {
        x = 1.0 * i;                                 /* x值*/

        for (n = 1; n < 4; n++) {                    /* n值*/
            y = chii(x, n);                            /* 卡方分布函数*/
            printf("P(%2.1f,%d)=%e ", x, n, y);       /* 打印结果*/
        }

        printf("\n");
    }

    getchar();
}
