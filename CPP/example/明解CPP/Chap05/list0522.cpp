// 傳回陣列元素之參照的函數

#include <iostream>
using namespace std;

const int a_size = 5;		// 陣列a的元素數
int a[a_size];

//--- 傳回a[idx]的參照---//
int& r(int idx)
{
	return a[idx];			// 傳回指向a[idx]的參照
}

int main()
{
	for (int i = 0; i < a_size; i++)
		r(i) = i;

	for (int i = 0; i < a_size; i++)
		cout << "r(" << i << ") = " << r(i) << '\n';

	return 0;
}
