#include "stdio.h"
#include "lagr1.c"
#include "lagr2.c"
#include "lagr7.c"
main()
{
    double t, z;
    double x[10] = {0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00};
    double y[10] = {2.1152, 2.2614, 2.4399, 2.6518, 2.8987,
                    3.1821, 3.5038, 3.8655, 4.2696, 4.7183
                   };
    t = 0.20;
    z = lagr1(x, y, 10, t);                           /* 拉格朗日一次插值*/
    printf("Lagrange 1: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = lagr2(x, y, 10, t);                           /* 拉格朗日二次插值*/
    printf("Lagrange 2: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = lagr7(x, y, 10, t);                           /* 拉格朗日七次插值*/
    printf("Lagrange 7: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    t = 0.55;
    printf("\n");
    z = lagr1(x, y, 10, t);                           /* 拉格朗日一次插值*/
    printf("Lagrange 1: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = lagr2(x, y, 10, t);                           /* 拉格朗日二次插值*/
    printf("Lagrange 2: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = lagr7(x, y, 10, t);                           /* 拉格朗日七次插值*/
    printf("Lagrange 7: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
}
