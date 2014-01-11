// 以實數值來求取兩個整數值的平均值

#include <iostream>
using namespace std;

int main()
{
	int x, y;

	cout << "求取兩個整數值x和y的平均值。\n";
	cout << "x的值：";	cin >> x;		// 讀入整數值到x 
	cout << "y的值：";	cin >> y;		// 讀入整數值到y 

	double ave = static_cast<double>(x + y) / 2; 	//以實數求取平均值
	cout << "x和y的平均值是" << ave << "。\n";	//顯示平均值

	return 0;
}
