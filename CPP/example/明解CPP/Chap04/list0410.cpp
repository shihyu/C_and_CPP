// 顯示關係運算子、相等運算子、邏輯否定運算子所產生的值

#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cout << "整數a, b：";
	cin >> a >> b;

	cout << boolalpha;
	cout << "a <  b = " << (a <  b) << '\n';
	cout << "a <= b = " << (a <= b) << '\n';
	cout << "a >  b = " << (a >  b) << '\n';
	cout << "a >= b = " << (a >= b) << '\n';
	cout << "a == b = " << (a == b) << '\n';
	cout << "a != b = " << (a != b) << '\n';
	cout << "!a     = " << (!a)     << '\n';
	cout << "!b     = " << (!b)     << '\n';

	return 0;
}
