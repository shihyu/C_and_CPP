// 顯示讀入的整數值以下的奇數

#include <iostream>
using namespace std;

int main ()
{
	int n;
	cout << "整數值：";
	cin >> n;

	for (int i = 1; i <= n; i += 2)
		cout << i << '\n';

	return 0;
}
