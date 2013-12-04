// 利用函數來求取兩個整數值的總和與乘積 (錯誤)

#include <iostream>
using namespace std;

//--- 求取x和y的總和並指定給sum，而乘積則指定給mul (錯誤)---//
void sum_mul(int x, int y, int sum, int mul)
{
	sum = x + y;
	mul = x * y;
}

int main()
{
	int a, b;
	int wa = 0, seki = 0;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;

	sum_mul(a, b, wa, seki);

	cout << "總和是" << wa << "\n";
	cout << "乘積是" << seki << "\n";

	return 0;
}
