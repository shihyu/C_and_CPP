// 繼承與解構子

#include <iostream>
using namespace std;

//--- 基底類別 ---//
class Base {
public:
     Base() { cout << "Base的建構子\n"; }		               // 建構子
   ~Base() { cout << "Base的解構子\n"; }			// 解構子
};

//--- 衍生類別 ---//
class Derived : public Base {
	int* a;
public:
   Derived() {	a = new int[10]; cout << "建立陣列。\n"; }             // 建構子
   ~Derived() { delete[] a; 	 cout << "解放陣列。\n"; }                     // 解構子
};

int main()
{
	Base* ptr = new Derived();		                                // 建立Derived

	delete ptr;						// 刪除Base

	return 0;
}
