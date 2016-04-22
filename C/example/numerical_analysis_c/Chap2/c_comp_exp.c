/*======================================================
//函数名：c_comp_pow.c
//功能描述：求复数指数
//输入参数：a（输入的结构体）
//          c（计算结果的结构体）
//返回值：0（失败），1（成功）
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "c_comp_product.c"

/*struct c_comp{
    double rmz;
    double imz;
}c_comp;
*/
int c_comp_exp(a, c)
struct c_comp* a, *c;
{
    double R;

    if (a == NULL || c == NULL) {
        printf("(c_comp_exp)The c_comp pointer is NULL!\n");
        return (0);
    }

    R = exp(a->rmz);

    c->rmz = R * cos(a->imz);
    c->imz = R * sin(a->imz);

    return (1);
}