#include <iostream>
using namespace std;
#define VIRTUAL_INHERITANCE_EN 0 

class A {
public:
    A() {
        cout << "A Constructor" << endl;
    }
};

#if VIRTUAL_INHERITANCE_EN
class B1: virtual public A {
#else
class B1: public A {
#endif
public:
    B1() {
        cout << "B1 Constructor" << endl;
    }
};

#if VIRTUAL_INHERITANCE_EN
class B2: virtual public A {
#else
class B2: public A {
#endif
public:
    B2() {
        cout << "B2 Constructor" << endl;
    }
};

class C: public B1, B2 {
public:
    C() {
        cout << "C Constructor" << endl;
    }
};

int main(void) {

    C a;

    return 0;
}
