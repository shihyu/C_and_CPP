// 將1, 2, 3, 4, 5指定給陣列的各個元素並顯示

#include <iostream>
using namespace std;

int main()
{
	int a[5];		// 元素型態為int型態且元素數為5的陣列

	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;

	cout << "a[" << 0 << "] = " << a[0] << '\n';
	cout << "a[" << 1 << "] = " << a[1] << '\n';
	cout << "a[" << 2 << "] = " << a[2] << '\n';
	cout << "a[" << 3 << "] = " << a[3] << '\n';
	cout << "a[" << 4 << "] = " << a[4] << '\n';

	return 0;
}
