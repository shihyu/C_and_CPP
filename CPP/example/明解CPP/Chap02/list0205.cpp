// 判斷讀入的整數值的正負並顯示

#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "整數值：";
	cin >> n;

	if (n > 0)
		cout << "該值為正值。\n";
	else if (n < 0)
		cout << "該值為負值。\n";
	else
		cout << "該值為0。\n";

	return 0;
}
