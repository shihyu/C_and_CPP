#include "stdio.h"
#include "stdlib.h"
#include "randu01s.c"
void main()
{
    int L;
    int flag, i, j;
    double* u_rand;
    L = 100;                                     /*生成10个随机数*/
    u_rand = (double*)malloc(L * sizeof(double)); /*动态分配空间*/

    if (u_rand == NULL) {
        printf("memory alloc failed.\n");
        exit(0);
    }

    flag = randu01s(L, u_rand);                /*调用函数*/

    if (!flag) {
        printf("ERROR!\n");
        exit(0);
    }

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 5; j++) {
            printf("%5.4f ", u_rand[i * 5 + j]);
        }

        printf("\n");
    }
}