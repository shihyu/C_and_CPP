// 複製陣列的所有元素並顯示

#include <iostream>
using namespace std;

int main()
{
	const int n = 5;		// 陣列a和b的元素數
	int a[n], b[n] = {0};		// 以0初始化陣列b的所有元素

	for (int i = 0; i < n; i++) {	// 將值讀入到陣列a
		cout << "a[" << i << "] : ";
		cin >> a[i];
	}

	for (int i = 0; i < n; i++)		// 複製陣列a的所有元素到陣列b
		b[i] = a[i];

	for (int i = 0; i < n; i++)		// 顯示陣列b
		cout << "b[" << i << "] = " << b[i] << '\n';

	return 0;
}
