// 整數陣列類別IntArray（第3版）的使用範例

#include <iomanip>
#include <iostream>
#include "IntArray.h"
using namespace std;

int main()
{
	int n;
	cout << "a的元素數：";
	cin >> n;

	IntArray a(n);				// 元素數為n個
	for (int i = 0; i < a.Size(); i++)
		a[i] = i;

	IntArray b(1000);
	cout << "b的元素數從" << b.Size();
	b = a;						// 指定
	cout << "變成" << b.Size() << "了。\n";

	IntArray c = b;				// 初始化

	cout << "    a    b    c\n";
	cout << "---------------\n";
	for (int i = 0; i < n; i++)
		cout << setw(5) << a[i] << setw(5) << b[i] << setw(5) << c[i] << '\n';

	return 0;
}
