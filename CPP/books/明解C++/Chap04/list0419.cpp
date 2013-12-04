// 將1, 2, 3, 4, 5指定給陣列的各個元素並顯示 (for敘述)

#include <iostream>
using namespace std;

int main()
{
	int a[5];		// 元素型態為int型態且元素數為5的陣列

	for (int i = 0; i < 5; i++)
		a[i] = i + 1;

	for (int i = 0; i < 5; i++)
		cout << "a[" << i << "] = " << a[i] << '\n';

	return 0;
}
