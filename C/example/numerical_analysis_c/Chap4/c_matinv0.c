#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "c_comp.c"
#include "c_matmul.c"
#include "c_matinv.c"

void main()
{
    struct c_comp c_mat[2][2], c_mat1[2][2], c_mat2[2][2];
    int i, j;
    int m, n;
    m = 2;
    n = 2;

    c_mat[0][0].rmz = 2;
    c_mat[0][0].imz = 3;
    c_mat[0][1].rmz = 0;
    c_mat[0][1].imz = 2;
    c_mat[1][0].rmz = 2;
    c_mat[1][0].imz = 1;
    c_mat[1][1].rmz = 1;
    c_mat[1][1].imz = 0.5;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            c_mat1[i][j] = c_mat[i][j];
        }

    printf("A:\n");

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f + (%2.5f)*i ", c_mat[i][j].rmz, c_mat[i][j].imz);
        }

        printf("\n");
    }

    printf("\n");

    c_mat_inv(c_mat, n);

    printf("inv(A):\n");

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f + (%2.5f)*i ", c_mat[i][j].rmz, c_mat[i][j].imz);
        }

        printf("\n");
    }

    printf("\n");

    printf("A*inv(A):\n");
    c_mat_mul(c_mat, c_mat1, n, n, n, c_mat2);

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%2.5f + (%2.5f)*i ", c_mat2[i][j].rmz, c_mat2[i][j].imz);
        }

        printf("\n");
    }

    getch();
}
