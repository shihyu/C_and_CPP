#include "stdio.h"
#include "popo.c"
#include "qcks.c"
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

    printf("Quick Sort:\n");                /* 快速排序的结果*/
    qcks(p, 0, 49);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("Bubble Sort:\n");              /* 气泡排序的结果*/
    popo(p, 50);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }
}
