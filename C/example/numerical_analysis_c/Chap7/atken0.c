#include "stdio.h"
#include "atken.c"
#include "atkene.c"
#include "lagr7.c"
main()
{
    double t, h, z, eps;
    double x[10] = {0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00};
    double y[10] = {2.1152, 2.2614, 2.4399, 2.6518, 2.8987,
                    3.1821, 3.5038, 3.8655, 4.2696, 4.7183
                   };
    eps = 1.0e-6;
    h = 0.1;
    t = 0.20;
    z = lagr7(x, y, 10, t);                           /* 拉格朗日七次插值*/
    printf("Lagrange 7: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = atken(x, y, 10, t, eps);                      /* 埃特金不等距插值*/
    printf("atken: t=%2.5f,z=%2.5f\n", t, z);         /* 打印结果*/
    z = atkene(x[0], h, y, 10, t, eps);               /* 埃特金等距插值*/
    printf("atkene: t=%2.5f,z=%2.5f\n", t, z);         /* 打印结果*/
    t = 0.55;
    printf("\n");
    z = lagr7(x, y, 10, t);                           /* 拉格朗日七次插值*/
    printf("Lagrange 7: t=%2.5f,z=%2.5f\n", t, z);    /* 打印结果*/
    z = atken(x, y, 10, t, eps);                      /* 埃特金不等距插值*/
    printf("atken: t=%2.5f,z=%2.5f\n", t, z);         /* 打印结果*/
    z = atkene(x[0], h, y, 10, t, eps);               /* 埃特金等距插值*/
    printf("atkene: t=%2.5f,z=%2.5f\n", t, z);         /* 打印结果*/
}
