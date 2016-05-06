
//7FALSE0.C
#include "stdio.h"
#include "7false.c"
main()       //主函数
{
    int k;
    double x, func(double);
    k = false(1.0, 3.0, 0.000001, func, &x);   //执行试位法
    printf("迭代次数 = %d\n", k);
    printf("一个实根为：%13.6e\n", x);
}

double func(double x)    //计算方程左端函数f(x)值
{
    double y;
    y = x * x * x - 2 * x * x + x - 2;
    return y;
}

//x = 2
//迭代24次
