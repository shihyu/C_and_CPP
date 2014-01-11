// 堆疊抽象類別範本Stack的使用範例（其2）

#include <iostream>
#include "Stack.h"
using namespace std;

//--- 彈出所有資料並顯示 ---//
void PopAll(Stack<int>& s)
{
	try {
		while (1)
			cout << s.Pop() << '\n';
	} catch (Stack<int>::EmptyErr) {
		return;
	}
}

int main()
{
	VecStack<int>  x;		// 向量版堆疊
	ListStack<int> y;		// 線形清單版堆疊

	x.Push(10);
	x.Push(11);
	x.Push(12);
	x.Push(13);

	y.Push(20);
	y.Push(21);
	y.Push(22);

	cout << "堆疊x\n";
	PopAll(x);

	cout << "堆疊y\n";
	PopAll(y);

	return 0;
}
