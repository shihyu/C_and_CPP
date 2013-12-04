// 將讀入的整數加總 (輸入0就結束)

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
		cout << "整數 (輸入0就結束)：";
		cin >> t;
		if (t == 0) break;		// 跳出for敘述
		sum += t;
	}
	cout << "總和為" << sum << "。\n";

	return 0;
}
