// 顯示九九乘法表

#include <iomanip>
#include <iostream>
using namespace std;

int main ()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++)
			cout << setw (3) << i * j;
		cout << '\n';
	}

	return 0;
}
