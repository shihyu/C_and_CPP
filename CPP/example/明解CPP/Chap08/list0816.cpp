// 標示符合條件的元素

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

//--- 值為30 ~ 60 ---//
bool f(int x)
{
	return (x >= 30 && x <= 60);
}

//--- 標示陣列a 之中函數f(x)為真的元素 ---//
void ary_disp(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		if (f(a[i]))
			cout << "★";
		else
			cout << "☆";
		cout << "a[" << i << "] = " << a[i] << '\n';
	}
}

int main()
{
	srand(time(NULL));			// 將亂數的種初始化
	int a[10];					// 元素型態為int 型態且元素數為10的陣列

	for (int i = 0; i < 10; i++)
		a[i] = rand() % 100;	// 指定0 ~ 99的亂數

	ary_disp(a, 10);

	return 0;
}
