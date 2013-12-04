// 將亂數指定給陣列的所有元素並顯示

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));		// 初始化亂數的種子
	int a[5];					// 元素型態為int型態且元素數為5的陣列

	for (int i = 0; i < 5; i++)
		a[i] = rand() % 10;		// 指定0～9的亂數

	for (int i = 0; i < 5; i++)
		cout << "a[" << i << "] = " << a[i] << '\n';

	return 0;
}
