//以0.001為單位從0.0遞增到1.0並顯示其總和 (以int來控制迴圈)

#include <iostream>
using namespace std;

int main()
{
	float sum = 0.0;
	for (int i = 0; i <= 1000; i++) {
		float x = float(i) / 1000;
		cout << "x = " << x << '\n';
		sum += x;
	}
	cout << "sum = " << sum << '\n';

	return 0;
}
