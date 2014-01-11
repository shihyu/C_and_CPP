// 以0.001為單位從0.0遞增到1.0並顯示其總和 (以float來控制迴圈)

#include <iostream>
using namespace std;

int main()
{
	float sum = 0.0;
	for (float x = 0.0; x <= 1.0; x += 0.001) {
		cout << "x = " << x << '\n';
		sum += x;
	}
	cout << "sum = " << sum << '\n';

	return 0;
}
