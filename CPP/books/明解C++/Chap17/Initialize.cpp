// 虛擬基底類別與非虛擬基底類別的初始化

#include <iostream>
using namespace std;

class V1 {
public:
	V1() { cout << "將V1初始化\n"; }
};

class V2 {
public:
	V2() { cout << "將V2初始化\n"; }
};

class X : public virtual V1, public virtual V2 {
public:
	X() { cout << "將Ｘ初始化\n"; }
};

class Y : public virtual V2, public virtual V1 {
public:
	Y() { cout << "將Ｙ初始化\n"; }
};

class Z : public X, public Y {
public:
	Z() { cout << "將Ｚ初始化\n"; }
};

int main()
{
	Z dummy;

	return 0;
}
