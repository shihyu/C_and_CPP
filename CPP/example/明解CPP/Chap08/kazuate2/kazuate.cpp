// 猜數字遊戲 (第2版：主要部份)

#include <iostream>
#include "kazuate.h"
using namespace std;

int max_no = 9;				// 答案的最大值

int main()
{
	initialize();
	cout << "猜數字遊戲開始！\n";

	do {
		gen_no();
		int hantei;
		do {
			hantei = judge(input());
			if (hantei > 0)
				cout << "\a還要更小歐。\n";
			else if (hantei < 0)
				cout << "\a還要更大歐。\n";
		} while (hantei != 0);
		cout << "正確答案。\n";
	} while (confirm_retry());

	return 0;
}
