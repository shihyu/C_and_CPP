// 顯示字串常值的型態與長度

#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
	cout << "■字串常值\"ABC\"\n";
	cout << "  型態："   << typeid("ABC").name()
		 << "  長度：" << sizeof("ABC") << "\n\n";

	cout << "■字串常值\"\"\n";
	cout << "  型態："   << typeid("").name()
		 << "  長度：" << sizeof("") << "\n\n";

	cout << "■字串常值\"abc\\0def\"\n";
	cout << "  型態："   << typeid("abc\0def").name()
		 << "  長度：" << sizeof("abc\0def") << "\n\n";

	return 0;
}
