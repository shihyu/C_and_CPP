#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "r_matmul.c"
#include "sdminv.c"

void main()
{
    double r_mat[2][2] = {{3, 2}, {2, 5}};
    double r_mat1[2][2], r_mat2[2][2];
    int i, j;
    int n = 2;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            r_mat1[i][j] = r_mat[i][j];
        }

    printf("A:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f ", r_mat[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    sdminv(r_mat, n);

    printf("inv(A):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f ", r_mat[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    printf("A*inv(A):\n");
    r_matmul(r_mat, r_mat1, n, n, n, r_mat2);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f ", r_mat2[i][j]);
        }

        printf("\n");
    }
}
