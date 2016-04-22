#include "stdio.h"
#include "bsl1.c"
#include "bsl2.c"
main()
{
    int n, i;
    double x, y;

    for (i = 1; i <= 8; i++) {
        x = 1.0 * i;
        printf("x=%2.1f\n", x);                 /* 第一类整数阶贝塞尔函数*/

        for (n = 1; n <= 4; n++) {
            y = bsl1(n, x);
            printf("J(%d)=%1.8f ", n, y);
        }

        printf("\n");

        for (n = 1; n <= 4; n++) {              /* 第二类整数阶贝塞尔函数*/
            y = bsl2(n, x);
            printf("Y(%d)=%1.8f ", n, y);
        }

        printf("\n");
    }

    getchar();
}
