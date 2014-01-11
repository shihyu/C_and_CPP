// 顯示整數型態所能表現的值

#include <climits>
#include <iostream>
using namespace std;

int main()
{
	cout << "此處理器的整數型態所能表現的值。\n";

	cout << "char         ：" << CHAR_MIN  << "～" << CHAR_MAX  << '\n';
	cout << "signed char  ：" << SCHAR_MIN << "～" << SCHAR_MAX << '\n';
	cout << "unsigned char：" << 0         << "～" << UCHAR_MAX << '\n';

	cout << "short int：" << SHRT_MIN << "～" << SHRT_MAX << '\n';
	cout << "int      ：" << INT_MIN  << "～" << INT_MAX  << '\n';
	cout << "long int ：" << LONG_MIN << "～" << LONG_MAX << '\n';

	cout << "unsigned short int：" << 0 << "～" << USHRT_MAX << '\n';
	cout << "unsigned int      ：" << 0 << "～" << UINT_MAX  << '\n';
	cout << "unsigned long int ：" << 0 << "～" << ULONG_MAX << '\n';

	return 0;
}
