#include "stdio.h"
#include "hmt.c"
#include "hmte.c"
main()
{
    double t, z;
    double x[10] = {0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00};
    double y[10] = {2.1152, 2.2614, 2.4399, 2.6518, 2.8987,
                    3.1821, 3.5038, 3.8655, 4.2696, 4.7183
                   };
    double dy[10] = {1.3052, 1.6214, 1.9499, 2.2918, 2.6487,
                     3.0221, 3.4138, 3.8255, 4.2596, 4.7183
                    };
    t = 0.20;
    z = hmt(x, y, dy, 10, t);                       /* 埃尔米特插值*/
    printf("hermite: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = hmte(x[0], 0.1, y, dy, 10, t);              /* 埃尔米特等距插值*/
    printf("hermite: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    t = 0.55;
    printf("\n");
    z = hmt(x, y, dy, 10, t);                       /* 埃尔米特插值*/
    printf("hermite: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = hmte(x[0], 0.1, y, dy, 10, t);              /* 埃尔米特等距插值*/
    printf("hermite: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
}
