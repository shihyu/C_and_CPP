#include "stdio.h"
#include "bspl1.c"
#include "bspl2.c"
#include "bspl3.c"
#define PI 3.1415926
main()
{
    int k, m, n;
    double x[11] = {0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00};
    double y[11] = {1.0000, 0.8090, 0.3090, -0.3090, -0.8090,
                    -1.0000, -0.8090, -0.3090, 0.3090, 0.8090, 1.0000
                   };    /* xy赋初值*/
    double t[11] = {0.00, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95, 1.00}, z[11],
                   z1[11], z2[11];
    double y1, y2;

    n = 11;
    m = 11;
    y1 = 0.0;                                      /* 在边界处的一阶导数*/
    y2 = 0.0;
    bspl1(x, y, y1, y2, n, t, m, z, z1, z2);       /* 第一类边界条件*/
    printf("BSPL1: \n");

    for (k = 0; k < m; k++) {                      /* 打印结果*/
        printf("t=%2.5f: z=%2.5f,z1=%2.5f,z2=%2.5f\n", t[k], z[k], z1[k], z2[k]);
    }

    y1 = -4.0 * PI * PI;                            /* 在边界处的二阶导数*/
    y2 = -4.0 * PI * PI;
    bspl2(x, y, y1, y2, n, t, m, z, z1, z2);       /* 第二类边界条件*/
    printf("BSPL2: \n");

    for (k = 0; k < m; k++) {                      /* 打印结果*/
        printf("t=%2.5f: z=%2.5f,z1=%2.5f,z2=%2.5f\n", t[k], z[k], z1[k], z2[k]);
    }

    bspl3(x, y, n, t, m, z, z1, z2);               /* 第三类边界条件*/
    printf("BSPL3: \n");

    for (k = 0; k < m; k++) {                      /* 打印结果*/
        printf("t=%2.5f: z=%2.5f,z1=%2.5f,z2=%2.5f\n", t[k], z[k], z1[k], z2[k]);
    }
}
