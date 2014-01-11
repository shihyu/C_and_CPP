// 求取從1到n的總和

#include <iostream>
using namespace std;

int main ()
{
	int n;

	cout << "求取從1到n的總和。\n";
	do {
		cout << "n的值：";
		cin >> n;
	} while (n <= 0);

	int sum = 0;				// 合計
	int i = 1;
	while (i <= n) {
		sum += i;				// 將i加到sum
		i++;					// 遞增i
	}
	cout << "從1到" << n << "為止的總和是" << sum << "。\n";

	return 0;
}
