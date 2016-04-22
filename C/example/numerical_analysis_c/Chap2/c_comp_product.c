/*======================================================
//函数名：c_comp_product.c
//功能描述：求复数的乘法
//输入参数：a1（第一个乘数a的结构体）
//          a2（第二个乘数b的结构体）
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
int c_comp_product(a1, a2, c)
struct c_comp* a1, *a2, *c;
{
    double p, q, s;

    if (a1 == NULL || a2 == NULL || c == NULL) {
        printf("(c_comp_product)The c_comp pointer is NULL!\n");
        return (0);
    }

    p = (a1->rmz) * (a2->rmz);
    q = (a1->imz) * (a2->imz);
    s = (a1->rmz + a1->imz) * (a2->rmz + a2->imz);
    c->rmz = p - q;
    c->imz = s - p - q;
    return (1);
}