#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "r_matmul.c"
#include "Tminv.c"

void main()
{
    double r_mat1[5][5], r_mat2[5][5], r_mat3[5][5];
    int i, j, m, n, p;

    static double t1[5] = {12.0, 6.0, 3.0, 2.0, 1.0};
    static double t2[5] = {1.0, -3.0, -3.0, -4.0, -5.0};

    m = 5;
    n = 5;

    p = Tminv(t1, t2, n, r_mat1, 1e-14);

    if (p > 0) {
        for (i = 0; i < n; i++) {
            r_mat2[i][i] = t1[0];

            for (j = i + 1; j < n; j++) {
                r_mat2[i][j] = t1[j - i];
                r_mat2[j][i] = t2[j - i];
            }
        }

        printf("T:\n");

        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%2.5f ", r_mat2[i][j]);
            }

            printf("\n");
        }

        printf("\n");

        printf("inv(T):\n");

        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%2.5f ", r_mat1[i][j]);
            }

            printf("\n");
        }

        printf("\n");

        printf("T*inv(T):\n");
        r_matmul(r_mat1, r_mat2, n, n, n, r_mat3);

        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%2.5f ", r_mat3[i][j]);
            }

            printf("\n");
        }
    }
}

