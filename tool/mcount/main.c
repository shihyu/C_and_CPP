#include <stdlib.h>
#include <stdio.h>
extern void mcount(void);
void b(int i)
{
        printf("b:%d\n", i);
}
int a(int i)
{
        b(i);
        return 3;
}
int main()
{
        int i = 3;
        int k = a(i);
        return k;
}
