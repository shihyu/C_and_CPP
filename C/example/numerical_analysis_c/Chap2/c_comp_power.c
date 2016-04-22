/*======================================================
//函数名：c_comp_power.c
//功能描述：求复数的乘幂
//输入参数：a（底数的结构体）
//          n（指数）
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
int c_comp_power(a, c, n)
struct c_comp* a, *c;
int n;
{
    double R, theta;

    if (a == NULL || c == NULL) {
        printf("(c_comp_power)The c_comp pointer is NULL!\n");
        return (0);
    }

    theta = atan2(a->imz, a->rmz);
    R = sqrt(a->rmz * a->rmz + a->imz * a->imz);

    theta = n * theta;
    R = pow(R, n);

    c->rmz = R * cos(theta);
    c->imz = R * sin(theta);
    return (1);
}