// 將讀入的整數加總 (輸入9999就強制結束)

#include <iostream>
using namespace std;

int main ()
{
	int n;			//加總的個數
	cout << "將整數加總。\n";
	cout << "要加總幾個整數：";
	cin >> n;
	cout << "輸入9999就強制結束。\n";

	int sum = 0;		//總和
	for (int i = 0; i < n; i++) {
		int t;
		cout << "整數：";
		cin >> t;
		if (t == 9999)
			goto Exit;
		sum += t;
	}
	cout << "總和為" << sum << "。\n";

Exit:
	return 0;
}
