// 將陣列元素逆向排列並顯示

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	const int n = 7;			// 陣列a的元素數
	int a[n];

	srand(time(NULL));		// 將亂數的種子初始化
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 100;
		cout << "a[" << i << "] = " << a[i] << '\n';
	}

	for (int i = 0; i < n / 2; i++) {
		int t = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = t;
	}

	cout << "將元素的排列順序反轉了。\n";
	for (int i = 0; i < n; i++)
		cout << "a[" << i << "] = " << a[i] << '\n';

	return 0;
}
