// 求取x的三次方與y的二次方之總和

#include <iostream>
using namespace std;

//--- 傳回x的n次方 ---//
double power(double x, int n)
{
	double tmp = 1.0;

	while (n-- > 0)
		tmp *= x;	//將x提交到tmp 
	return tmp;
}

//--- 傳回x的三次方與y的二次方之總和 ---//
double cubx_plus_sqry(double x, double y)
{
	return power(x, 3) + power(y, 2);
}

int main()
{
	double x;
	double y;

	cout << "求取x的三次方與y的二次方之總和。\n";
	cout << "x的值：";	cin >> x;
	cout << "y的值：";	cin >> y;
	cout << "x的三次方與y的二次方之總和是" << cubx_plus_sqry(x, y) << "。\n";

	return 0;
}

