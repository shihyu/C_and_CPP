/*======================================================
//函数名：c_comp_cos.c
//功能描述：求复数的余弦
//输入参数：a（输入的结构体）
//          c（计算结果的结构体）
//返回值：0（失败），1（成功）
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*struct c_comp{
    double rmz;
    double imz;
}c_comp;
*/
int c_comp_cos(a, c)
struct c_comp* a, *c;
{
    double tmp1, tmp2;

    if (a == NULL || c == NULL) {
        printf("(c_comp_cos)The c_comp pointer is NULL!\n");
        return (0);
    }

    tmp1 = exp(a->imz);
    tmp2 = exp(-a->imz);
    c->rmz = cos(a->rmz) * (tmp1 + tmp2) / 2;
    c->imz = -sin(a->rmz) * (tmp1 - tmp2) / 2;

    return (1);
}