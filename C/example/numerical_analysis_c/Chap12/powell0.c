#include "stdio.h"
#include "math.h"
#include "powell.c"

void main()
{
    double  eps, fopt, x[3];
    int itmax = 50, n = 3, it;
    double f();
    double ee[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};  /* 初始的方向*/
    eps = 1e-7;
    x[0] = x[1] = x[2] =
                      2.0;                                               /* 初始点*/
    it = powell(x, ee, x, n, &fopt, f, eps,
                itmax);                         /* 调用函数，并打印结果*/
    printf("iterations = %d:\n x0=%f,x1=%f,x2=%f\nfopt=%f\n", it, x[0], x[1], x[2],
           fopt);
}

double f(x, n)
double* x;
int n;
{
    double y;

    if (n != 3) {
        return (0.0);
    }

    y = (x[0] - 1.0) * (x[0] - 1.0) + (x[1] - 2.0) * (x[1] - 2.0) + (x[2] - 3.0) *
        (x[2] - 3.0);
    return y;
}