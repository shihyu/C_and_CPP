// 以1, 2, 3, 4, 5來初始化陣列的各個元素並顯示 (透過計算來求取元素數)

#include <iostream>
using namespace std;

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int a_size = sizeof(a) / sizeof(a[0]);	// 陣列a的元素數

	for (int i = 0; i < a_size; i++)
		cout << "a[" << i << "] = " << a[i] << '\n';

	return 0;
}
