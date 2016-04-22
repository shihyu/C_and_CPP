#include "stdio.h"
#include "stdlib.h"
#include "randuabs.c"
void main()
{
    int L, a, b;
    int i, flag, j, uab_rand[100];
    L = 100;
    a = -5;
    b = 10;
    flag = randuabs(L, a, b, uab_rand);        /*µ÷ÓÃº¯Êý*/

    if (!flag) {
        printf("ERROR!\n");
        exit(0);
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%3d ", uab_rand[i * 10 + j]);
        }

        printf("\n");
    }
}
