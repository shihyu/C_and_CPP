// 讀入六個人的分數並顯示總分與平均

#include <iostream>
using namespace std;

int main()
{
	int yamane, takada, kawakami, koga, tozuka, saegusa;// 分數
	int sum = 0;										// 總和

	cout << "求取六個人的分數之總分與平均。\n";
	cout << "1號的分數：";   cin >> yamane;	  sum += yamane;
	cout << "2號的分數：";   cin >> takada;	  sum += takada;
	cout << "3號的分數：";   cin >> kawakami; sum += kawakami;
	cout << "4號的分數：";   cin >> koga;	  sum += koga;
	cout << "5號的分數：";   cin >> tozuka;	  sum += tozuka;
	cout << "6號的分數：";   cin >> saegusa;  sum += saegusa;

	cout << "總分是" << sum << "分。\n";
	cout << "平均是" << double(sum) / 6 << "分。\n";

	return 0;
}
