#include "c_comp.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "c_comp_product.c"
#include "c_comp_divide.c"

void main()
{
    struct c_comp a, b, c, d;
    a.rmz = 7.0;
    a.imz = 3.0;
    b.rmz = 2.3;
    b.imz = -4.5;

    if (c_comp_product(&a, &b, &c)) {
        printf("乘法结果为：");
        printf("%1.5f+j%1.5f\n", c.rmz, c.imz);
    }

    if (c_comp_divide(&a, &b, &d)) {
        printf("除法结果为：");
        printf("%1.5f+j%1.5f\n", d.rmz, d.imz);
    }
}
