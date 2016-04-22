#include "stdio.h"
#include "tzi1.c"
#include "lfsi.c"
main()
{
  double a,b,eps,h0,z;
  double f1(double);
  a = 0.0;
  b = 4.0;
  eps = 1e-8;
  h0 = 1e-5;
  z=tzi1(a,b,4,eps,h0,f1);                     /* 用变步长梯形求积法积分*/
  printf("tzi1: t=%2.5f\n",z);                 /* 打印结果*/
  z=lfsi(a,b,4,eps,f1);                        /* 用连分式求积法积分*/
  printf("lfsi: t=%2.5f\n",z);
  getchar();
}

#include "math.h"
double f1(x)
double x;                                      /* 被积分的函数*/
{
  double y;
    y=exp(-x*x)/(1.0+x*x);
  return(y);
}
