// 猜數字遊戲 (第2版：輸出入部份)

#include <iostream>
#include "kazuate.h"
using namespace std;

//--- 要求輸入  ---//
static void prompt()
{
	cout << "從0開始到" << max_no
		 << "為止的數字：";
}

//--- 讀入解答  ---//
int input()
{
	int kazu;
	do {
		prompt();
		cin >> kazu;
	} while (kazu < 0 || kazu > max_no);
	return kazu;
}

//--- 確認是否繼續 ---//
bool confirm_retry()
{
	int cont;
	cout << "要再來一次嗎？\n"
		 << "<Yes ... 1 / No ... 0>：";
	cin >> cont;
	return bool(cont);
}
