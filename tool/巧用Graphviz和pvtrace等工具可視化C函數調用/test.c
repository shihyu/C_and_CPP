#include  <stdio.h>
#include  <stdlib.h>

void test1() {
    printf("in test1.\n");
}
void test2() {
    test1();
    printf("in test2.\n");
}
void test3() {
    test1();
    test2();
    printf("in test3.\n");
}
int main(int argc ,  char*   argv []) {
    printf("Hello wolrd.\n");
    test1();
    test2();
    test3();
    return  0 ;
}
