#include "stdio.h"
#include "toepl.c"
main()
{
  int i;
  double x[5];
  double t[5]={3.0,2.5,3.5,1.5,0.5};         /* 托伯利兹矩阵*/
  double b[5]={2.0,3.0,4.0,5.0,6.0};         /* 常数矩阵*/
  if(toepl(t,b,x,5,1e-12)>0)                     /* 调用函数求解并打印结果*/
  for(i=0; i<5; i++)
    printf("x(%d)=%2.5f\n",i,x[i]);
}

