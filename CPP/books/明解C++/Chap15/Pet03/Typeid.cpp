// 顯示指向基底類別之指標所指的物件之型態

#include <iostream>
#include <typeinfo>
#include "Pet.h"
using namespace std;

int main()
{
	Pdog d;			// 狗
	Pcat c;			// 貓
	Pmonkey m;		// 猴
	Pet* p;			// 指向動物類別（基底類別）的指標

	p = &d;
	cout << "p所指的是" << typeid(*p).name() << "型態的物件。\n";

	p = &c;
	cout << "p所指的是" << typeid(*p).name() << "型態的物件。\n";

	p = &m;
	cout << "p所指的是" << typeid(*p).name() << "型態的物件。\n";

	return 0;
}
