// 以讀入的個數來顯示*

#include <iostream>
using namespace std;

int main ()
{
	int n;
	cout << "要顯示幾個*：";
	cin >> n;

	for (int i = 0; i < n; i++)
		cout << '*';
	cout << '\n';

	return 0;
}
