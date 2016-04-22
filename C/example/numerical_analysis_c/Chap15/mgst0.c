#include "stdio.h"
#include "mgst.c"
main()
{
    int i, j, p[50];
    printf("Data:\n");

    for (i = 0; i < 5; i++) {              /* 生成一些无序数据*/
        for (j = 0; j < 10; j++) {
            p[10 * i + j] = 20 + 10 * i - j ;
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("Merge Sort:\n");                /* 直接选择排序的结果*/
    mgst(p, 50);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }
}
