// 動態產生整數陣列物件

#include <iostream>
using namespace std;

int main()
{
	int asize;						// 陣列的元素數
	cout << "元素數：";
	cin >> asize;

	int* a = new int[asize];			// 產生

	for (int i = 0; i < asize; i++)
		a[i] = i;

	for (int i = 0; i < asize; i++)
		cout << "a[" << i << "] = " << a[i] << '\n';

	delete[] a;					// 丟棄

	return 0;
}
