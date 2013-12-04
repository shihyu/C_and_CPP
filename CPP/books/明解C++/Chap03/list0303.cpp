// 猜數字遊戲 (猜0~99)

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main ()
{
	srand (time (NULL));		// 設定亂數的種子
	int no = rand () % 100;		// 要猜的數字：產生0～99的亂數
	int x;
	cout << "猜數字遊戲開始!!\n";
	cout << "請猜0~99的數字。\n";

	do {
		cout << "哪個數字：";
		cin >> x;
		if (x > no)
			cout << "\a是更小的數字喔。\n";
		else if (x < no)
			cout << "\a是更大的數字喔。\n";
	} while (x != no);
	cout << "正確答案。\n";

	return 0;
}
