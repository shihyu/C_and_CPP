// 讀入ninzu個人的分數並顯示總分與平均

#include <iostream>
using namespace std;

int main()
{
	const int ninzu = 6;	// 人數
	int tensu[ninzu];		// ninzu人的分數
	int sum = 0;			// 總和

	cout << "求取" << ninzu << "個人的分數之總分與平均。\n";
	for (int i = 0; i < ninzu; i++) {
		cout << i + 1 << "號的分數：";
		cin >> tensu[i];		//讀入tensu[i]
		sum += tensu[i];		//將tensu[i]加到sum 
	}

	cout << "總分是" << sum << "分。\n";
	cout << "平均是" << double(sum) / ninzu << "分。\n";

	return 0;
}
