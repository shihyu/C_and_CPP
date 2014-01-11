// 多重繼承（基底類別的初始化、驗證模糊性的控制）

#include <iostream>
using namespace std;

//===== 基底類別１ =====//
class Base1 {
public:
	int x;

	Base1(int a = 0) : x(a) {				// 建構子
		cout << "將Base1::x以" << x << "來初始化。\n";
	}

	void Print() { cout << "這是Base1類別：x = " << x << '\n'; }
};

//===== 基底類別２ =====//
class Base2 {
public:
	int x;

	Base2(int a = 0) : x(a) {				// 建構子
		cout << "將Base2::x以" << x << "來初始化。\n";
	}

	void Print() { cout << "這是Base2類別：x = " << x << '\n'; }
};

//===== 衍生類別 =====//
class Derived : public Base1, public Base2 {
	int y;

public:
	Derived(int a, int b, int c) : y(c), Base2(a), Base1(b) {   // 建構子
		cout << "將Derived::y以" << y << "來初始化。\n";
	}

 	void func(int a, int b) {
	//	x = 1;					// 錯誤：模糊
		Base1::x = a;
		Base2::x = b;
	}
};

int main()
{
	Derived z(1, 2, 3);

	z.func(1, 2);
//	z.Print();					// 錯誤：模糊
	z.Base1::Print();
	z.Base2::Print();

	return 0;
}
