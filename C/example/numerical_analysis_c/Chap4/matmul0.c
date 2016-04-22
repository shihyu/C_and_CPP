#include "stdio.h"
#include "stdlib.h"
#include "c_comp.c"                              /* 需要包含复数运算的文件*/
#include "c_matmul.c"                            /* 实系数矩阵相乘和复系数矩阵相乘的函数*/
#include "r_matmul.c"

void main()
{
    struct c_comp c_mat1[2][2], c_mat2[2][2], c_mat3[2][2];

    double r_mat1[3][2] = {{1, 2}, {3, 4}, {1, 4}}; /* 为要相乘的实矩阵赋初值*/
    double r_mat2[2][2] = {{5, 6}, {7, 8}};
    double r_mat3[3][2];
    int i, j;

    r_matmul(r_mat1, r_mat2, 3, 2, 2, r_mat3);   /* 调用函数进行计算并打印结果*/
    printf("real matmul:\n");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            printf("%2.5f ", r_mat3[i][j]);
        }

        printf("\n");
    }

    c_mat1[0][0].rmz = 1;
    c_mat1[0][0].imz = 1;  /* 为要相乘的复矩阵赋初值*/
    c_mat1[0][1].rmz = 0;
    c_mat1[0][1].imz = 1;
    c_mat1[1][0].rmz = 1;
    c_mat1[1][0].imz = 0;
    c_mat1[1][1].rmz = 2;
    c_mat1[1][1].imz = 3;
    c_mat2[0][0].rmz = 2;
    c_mat2[0][0].imz = 3;
    c_mat2[0][1].rmz = 0;
    c_mat2[0][1].imz = 2;
    c_mat2[1][0].rmz = 2;
    c_mat2[1][0].imz = 1;
    c_mat2[1][1].rmz = 1;
    c_mat2[1][1].imz = 0.5;
    c_matmul(c_mat1, c_mat2, 2, 2, 2, c_mat3);   /* 调用函数进行计算并打印结果*/
    printf("complex matmul:\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%2.5f + (%2.5f)*i ", c_mat3[i][j].rmz, c_mat3[i][j].imz);
        }

        printf("\n");
    }
}
