#include "conio.h"
#include "stdio.h"
#include "r_mlu.c"
#include "r_matmul.c"

main()
{
    int i, j, n;
    double p[4][4], q[4][4], l[4][4], u[4][4], mat1[4][4], mat2[4][4], mat3[4][4];
    double mat[4][4] = { {1.0, 2.0, 3.0, 4}, {1.0, 4.0, 9.0, 16.0},
        {1.0, 8.0, 27.0, 64.0}, {1.0, 16.0, 81.0, 256.0}
    };

    n = 4;
    i = r_mlu(mat, n, l, u, p, q, 1e-10);

    r_matmul(l, u, n, n, n, mat1);
    r_matmul(p, mat1, n, n, n, mat2);
    r_matmul(mat2, q, n, n, n, mat3);
    printf("L*U:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%5.2f ", mat1[i][j]);
        }

        printf("\n");
    }

    printf("P*A*Q:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%5.2f ", mat3[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}