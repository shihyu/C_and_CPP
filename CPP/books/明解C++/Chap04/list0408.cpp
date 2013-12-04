// 顯示各種變數和常數的型態資訊

#include <iostream>
#include <typeinfo>
using namespace std;
 
int main()
{
	char c;
	short h;
	int i;
	long l;

	cout << "變數c的型態：" << typeid(c).name() << '\n';
	cout << "變數h的型態：" << typeid(h).name() << '\n';
	cout << "變數i的型態：" << typeid(i).name() << '\n';
	cout << "變數l的型態：" << typeid(l).name() << '\n';

	cout << "字元常值'A'的型態："   << typeid('A').name() << '\n';
	cout << "整數常值100的型態："   << typeid(100).name() << '\n';
	cout << "整數常值100U的型態："  << typeid(100U).name() << '\n';
	cout << "整數常值100L的型態："  << typeid(100L).name() << '\n';
	cout << "整數常值100UL的型態：" << typeid(100UL).name() << '\n';

	return 0;
}
