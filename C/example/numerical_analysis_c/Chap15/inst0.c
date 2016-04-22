#include "stdio.h"
#include "inst.c"
#include "shel.c"
main()
{
    int i, j, p[50], p1[50];
    printf("Data:\n");

    for (i = 0; i < 5; i++) {              /* 生成一些无序数据*/
        for (j = 0; j < 10; j++) {
            p[10 * i + j] = 20 + 10 * i - j ;
            p1[10 * i + j] = p[10 * i + j];
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("Insert Sort:\n");                /* 直接插入排序的结果*/
    inst(p, 50);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("Shell Sort:\n");                /* 希尔排序的结果*/
    shel(p1, 50);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d   ", p1[10 * i + j]);
        }

        printf("\n");
    }
}
