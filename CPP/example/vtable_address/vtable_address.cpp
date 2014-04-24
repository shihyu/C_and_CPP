#include <iostream>
using namespace std;

class Base {
public :
    virtual void f() {
        cout << "Base::f" << endl;
    }
    virtual void g() {
        cout << "Base::g" << endl;
    }
    virtual void h() {
        cout << "Base::h" << endl;
    }

private:
    int a;
    int b;
};

int
main(int argc, char **argv) {

    typedef void (*Fun)(void);
    Base b;
    Fun pFun = NULL;

    cout << "b instance " << sizeof(b) << endl;  

    cout << "虛函數表地址：" << (unsigned long *)(&b) << endl;
    cout << "虛函數表— 第一個函數地址：" << (unsigned long *)*(unsigned long *)(&b) << endl;

    // Invoke the first virtual function
    pFun = (Fun) * ((unsigned long *) * (unsigned long *)(&b) + 0);
    pFun();
    pFun = (Fun) * ((unsigned long *) * (unsigned long *)(&b) + 1);
    pFun();
    pFun = (Fun) * ((unsigned long *) * (unsigned long *)(&b) + 2);
    pFun();

    return 0;
}

