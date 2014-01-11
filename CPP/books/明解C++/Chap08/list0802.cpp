// 求得陣列之最大值(使用多載)

#include <iostream>
using namespace std;

//--- 傳回元素數為n的陣列x之最大值(int型態) ---//
int maxof(const int x[], int n)
{
	int max = x[0];
	for (int i = 1; i < n; i++)
		if (x[i] > max)
			max = x[i];
	return max;
}

//--- 傳回元素數為n的陣列x之最大值(double型態) ---//
double maxof(const double x[], int n)
{
	double max = x[0];
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
