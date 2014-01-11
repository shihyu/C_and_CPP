// 動態轉型與失敗時的行動

#include <iostream>
using namespace std;

//===== 基底類別 =====//
class Base {
	virtual void f() { }	// 虛擬函數
};

//===== 衍生類別 =====//
class Derived : public Base {

};

int main()
{
	Base base;
	Derived derived;

	Derived* p1 = dynamic_cast<Derived*>(&base);	         // 失敗：變為空指標
	Derived* p2 = dynamic_cast<Derived*>(&derived);          // 成功

	cout << "p1 = " << p1 << '\n';
	cout << "p2 = " << p2 << '\n';

	try {
		Derived& r1 = dynamic_cast<Derived&>(base);	    // 失敗：送出bad_cast
	} catch (bad_cast) {
		cout << "r1的強制轉型失敗\n";
	}

	try {
		Derived& r2 = dynamic_cast<Derived&>(derived);	// 成功
	} catch (bad_cast) {
		cout << "r2的強制轉型失敗\n";		            // 不會執行
	}

	return 0;
}
