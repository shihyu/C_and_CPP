// 求得陣列之最大值(使用函數範本)

#include <iostream>
using namespace std;

//--- 傳回元素數為n的Type型態陣列x的最大值的函數範本 ---//	 
template <class Type>
Type maxof(const Type x[], int n)
{
	Type max = x[0];
	for (int i = 1; i < n; i++)
		if (x[i] > max)
			max = x[i];
	return max;
}

int main()
{
	const int isize = 8;
	int ix[isize];

	// 整數陣列的最大值
	cout <<"請輸入"<< isize << "個整數。\n";
	for (int i = 0; i < isize; i++) {
		cout << i + 1 << ":";
		cin >> ix[i];
	}
	cout << "最大值為" << maxof(ix, isize) << "。\n\n";

	const int dsize = 5;
	double dx[dsize];

	// 實數陣列的最大值
	cout <<"請輸入"<< dsize << "個實數。\n";
	for (int i = 0; i < dsize; i++) {
		cout << i + 1 << ":";
		cin >> dx[i];
	}
	cout << "最大值為" << maxof(dx, dsize) << "。\n";

	return 0;
}
