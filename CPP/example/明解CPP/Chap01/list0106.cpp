// 顯示變數x和y的總和以及平均值 (變數是不定值)

#include <iostream>
using namespace std;

int main()
{
	int x;			// x是int型態的變數 (不定值)
	int y;			// y是int型態的變數 (不定值)

	cout << "x的值是" << x << "。\n";				// 顯示x的值
	cout << "y的值是" << y << "。\n";				// 顯示y的值
	cout << "總和是" << x + y << "。\n";			// 顯示x和y的總和
	cout << "平均值是" << (x + y) / 2 << "。\n";		// 顯示x和y的平均值

	return 0;
}
