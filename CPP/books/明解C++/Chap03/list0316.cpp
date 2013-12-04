// 將讀入的整數加總 (不加總負值)

#include <iostream>
using namespace std;

int main ()
{
	int n;			// 加總的個數
	cout << "將整數加總。\n";
	cout << "要加總幾個整數：";
	cin >> n;

	int sum = 0;		//總和
	for (int i = 0; i < n; i++) {
		int t;
		cout << "整數：";
		cin >> t;
		if (t < 0) {
			cout << "\a負數不進行加總。\n";
			continue;
		}
		sum += t;
	}
	cout << "總和為" << sum << "。\n";

	return 0;
}
