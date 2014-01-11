// 顯示陣列的型態和元素的型態

#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
	int a[5];
	double b[7];

	cout << "陣列a的型態：" << typeid(a).name()    << '\n';
	cout << "a的元素型態：" << typeid(a[0]).name() << '\n';
	cout << "陣列b的型態：" << typeid(b).name()    << '\n';
	cout << "b的元素型態：" << typeid(b[0]).name() << '\n';

	return 0;
}
