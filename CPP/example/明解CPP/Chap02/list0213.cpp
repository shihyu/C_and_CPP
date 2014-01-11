// 讀入的整數值可以被10整除嗎？

#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "整數值：";
	cin >> n;

	if (int m = n % 10) {
		cout << "該值不能被10整除。\n";
		cout << "最小位數是" << m << "。\n";
	} else {
		cout << "該值可以被10整除。\n";
	}

	return 0;
}
