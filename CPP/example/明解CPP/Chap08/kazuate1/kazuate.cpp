// 猜數字遊戲 (第1版：主要部份)

#include <iostream>
using namespace std;

void initialize();	                             		// [初始化]  基於現在時間來設定亂數的種
void gen_no();				// [製作問題]  以亂數產生0 ~ max_no 的值
int judge(int cand);		                                // [判斷答案]  判斷cand 是否為正確答案
int input();				// [輸入答案]  讓玩家輸入max_no 的值
bool confirm_retry();	                   	// [確認是否繼續]  確認是否再次進行遊戲

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
