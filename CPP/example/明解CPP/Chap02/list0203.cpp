// 讀入的兩個整數值是否相等

#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;

	if (a == b)
		cout << "兩個值相等。\n";
	else
		cout << "兩個值不相等。\n";

	return 0;
}
