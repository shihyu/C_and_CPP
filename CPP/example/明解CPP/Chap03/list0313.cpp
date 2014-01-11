// 顯示左下側為直角的直角三角形

#include <iostream>
using namespace std;

int main ()
{
	int n;
	cout << "顯示左下側為直角的直角三角形。\n";
	cout << "層數：";
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++)		// 顯示i個'*'
			cout << '*';
		cout << '\n';
	}

	return 0;
}
