// 讀入的整數值是否為正值

#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "整數值：";
	cin >> n;

	if (n > 0)
		cout << "該值為正值。\n";
	else
		cout << "該值為0或負值。\n";

	return 0;
}
