#include "stdio.h"
#include "smcg.c"
#include "jaco.c"
#include "gssd.c"
#include "orelax.c"
main()
{
    int i, j;
    double a[5][5] = {{24.0, 7.0, 5.0, 2.0, -1.0},
        {7.0, 21.0, 6.0, 3.0, -2.0},
        {5.0, 2.0, 17.0, -2.0, 1.0},
        {2.0, 3.0, -7.0, 21.0, 8.0},
        { -1.0, -2.0, 1.0, 4.0, 15.0}
    };
    double x[5], b[5] = {3.0, 1.5, -2.5, 2.0, 1.0}; /* 常数向量赋值*/
    i = jaco(a, b, x, 5, 1e-4, 30);              /* 调用雅克比迭代方法函数求解*/

    if (i != 0) {                                /* 打印结果*/
        printf("Jacobi:\n");

        for (i = 0; i < 5; i++) {
            printf("x(%d) = %2.5f\n", i, x[i]);
        }
    }

    printf("\n");
    i = gssd(a, b, x, 5, 1e-4,
             30);              /* 调用高斯-塞德尔迭代方法函数求解*/

    if (i != 0) {                                /* 打印结果*/
        printf("Gauss Seidel:\n");

        for (i = 0; i < 5; i++) {
            printf("x(%d) = %2.5f\n", i, x[i]);
        }
    }

    printf("\n");
    i = orelax(a, b, x, 5, 1.2, 1e-4, 30);       /* 调用超松驰迭代方法函数求解*/

    if (i != 0) {                                /* 打印结果*/
        printf("Overrelax:\n");

        for (i = 0; i < 5; i++) {
            printf("x(%d) = %2.5f\n", i, x[i]);
        }
    }

    printf("\n");
    i = smcg(a, b, x, 5, 1e-4, 30);              /* 调用共轭梯度迭代方法函数求解*/

    if (i != 0) {                                /* 打印结果*/
        printf("Conjugate Gradient:\n");

        for (i = 0; i < 5; i++) {
            printf("x(%d) = %2.5f\n", i, x[i]);
        }
    }
}
