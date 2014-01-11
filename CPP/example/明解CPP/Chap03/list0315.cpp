// 將讀入的整數加總 (在總和不超過1000的範圍內進行加總)

#include <iostream>
using namespace std;

int main ()
{
	int n;			// 加總的個數
	cout << "將整數加總。\n";
	cout << "要加總幾個整數：";
	cin >> n;

	int sum = 0;		// 總和
	for (int i = 0; i < n; i++) {
		int t;
		cout << "整數：";
		cin >> t;
		if (sum + t > 1000) {
			cout << "\a總和超過1000了。\n無視最後的數值。\n";
			break; 
		}
		sum += t;
	}
	cout << "總和為" << sum << "。\n";

	return 0;
}
