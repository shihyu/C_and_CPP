// 整數的二次方和浮動小數點數的二次方 (類似函數巨集)

#include <iostream>
using namespace std;

#define sqr(x)  ((x) * (x))

int main()
{
	int    n;
	double x;

	cout << "請輸入整數：";  cin >> n;
	cout << "該數的二次方是" << sqr(n) << "。\n";

	cout << "請輸入實數：";  cin >> x;
	cout << "該數的二次方是" << sqr(x) << "。\n";

	return 0;
}
