/*======================================================
//函数名：c_comp_log.c
//功能描述：求复数的对数
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
int c_comp_log(a, c)
struct c_comp* a, *c;
{

    if (a == NULL || c == NULL) {
        printf("(c_comp_log)The c_comp pointer is NULL!\n");
        return (0);
    }

    c->rmz = log(sqrt(a->rmz * a->rmz + a->imz * a->imz));
    c->imz = atan2(a->imz, a->rmz);

    return (1);
}