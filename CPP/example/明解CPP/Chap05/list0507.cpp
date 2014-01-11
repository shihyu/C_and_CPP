// 心算練習

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

//--- 確認是否繼續進行 ---//
bool confirm_retry()
{
	int cont;
	do {
		cout << "再一次嗎？<Yes…1／No…0>：";
		cin >> cont;
	} while (cont != 0 && cont != 1);
	return bool(cont);			// 傳回轉換成bool型態的值
}

int main()
{
	srand(time(NULL));
	cout << "心算練習開始!!\n";

	do {
		int x = rand() % 900 + 100;		// 三位數
		int y = rand() % 900 + 100;		// 三位數
		int z = rand() % 900 + 100;		// 三位數
		int k;						// 讀入的值
		while (true) {
			cout << x << " + " << y << " + " << z << " = ";
			cin >> k;
			if (k == x + y + z) break;
			cout << "\a錯了!!\n";
		}
	} while (confirm_retry());

	return 0;
}
