// 利用亂數產生0~9的幸運號碼並顯示

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));				// 設定亂數的種子

	int lucky = rand() % 10;				// 0~9的亂數

	cout << "今天的幸運號碼是" << lucky << "。\n";

	return 0;
}
