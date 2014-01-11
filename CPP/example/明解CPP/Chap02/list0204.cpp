// 讀入的整數值是否為0

#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "整數值：";
	cin >> n;

	if (!n)
		cout << "該值是0。\n";
	else
		cout << "該值不是0。\n";

	return 0;
}
