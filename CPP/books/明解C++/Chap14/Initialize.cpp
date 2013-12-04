// 用來確認基底類別與成員的初始化的類別群

#include <iostream>
using namespace std;

//--- Derived的基底類別 ---//
class Base {
	int x;
public:
	Base(int a = 0) : x(a) { cout << "將Base::x以" << x << "來初始化。\n"; }
};

//--- 包含在Derived之中的類別 ---//
class Memb {
	int x;
public:
	Memb(int a = 0) : x(a) { cout << "將Memb::x以" << x << "來初始化。\n"; }
};

//--- Derived會從Base開始public衍生 ---//
class Derived : public Base {
	int y;
	Memb m1;
	Memb m2;
	void say() { y = 0; cout << "將Derived::y以" << y << "來初始化。\n"; }

public:
	Derived()	                                                              { say(); }
	Derived(int a, int b, int c) : m2(a), m1(b), Base(c) { say(); }
};

int main()
{
	Derived d1;

	cout << '\n';

	Derived d2(1, 2, 3);

	return 0;
}
