class A {
public:
    void f() { / *…* / }
};

class B : public A {
public:
    virtual void f() { / *…* / }                    // 虛擬函數
};

class C : public B {
public:
    void f()    { / *…* / }     // 虛擬函數
    void f(int) { / *…* / } // 多載（overload）
};

