// 顯示變數x和y的總和以及平均值 (明確地初始化變數) 

#include <iostream>
using namespace std;

int main()
{
	int x = 63;		// x是int型態的變數 (以63初始化)
	int y = 18;		// y是int型態的變數 (以18初始化)

	cout << "x的值是" << x << "。\n";				// 顯示x的值
	cout << "y的值是" << y << "。\n";				// 顯示y的值
	cout << "總和是" << x + y << "。\n";				//顯示x和y的總和
	cout << "平均值是" << (x + y) / 2 << "。\n";		//顯示x和y的平均值

	return 0;
}
