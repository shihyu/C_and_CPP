// 將陣列的元素逆向排列

#include <iostream>
using namespace std;

//--- 將元素數為n的陣列a逆向排列 ---//
void reverse(int a[], int n)
{
	for (int i = 0; i < n /2; i++) {
		int t = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = t;
	}
}

int main()
{
	const int n = 5;
	int c[n];

	for (int i = 0; i < n; i++) {		// 讀入到陣列c
		cout << "c[" << i << "] : ";
		cin >> c[i];
	}
	reverse(c, n);					// 將陣列c逆向排列

	cout << "將元素逆向排列。\n";
	for (int i = 0; i < n; i++)			// 顯示陣列c
		cout << "c[" << i << "] = " << c[i] << '\n';

	return 0;
}
