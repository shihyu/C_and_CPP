// 整數陣列類別IntArray（第１版）的使用範例

#include <iostream>
#include "IntArray.h"
using namespace std;

int main()
{
	int n;

	cout << "請輸入元素數：";
	cin >> n;

	IntArray x(n);	// 元素數為n的陣列

	for (int i = 0; i < x.Size(); i++)	// 將值指定給各元素
		x[i] = i;

	for (int i = 0; i < x.Size(); i++)	// 顯示各元素的值
		cout << "x[" << i << "] = " << x[i] << '\n';

	return 0;
}
