// 弄せだ计陪ボ羆だ籔キА

#include <iostream>
using namespace std;

int main()
{
	int yamane, takada, kawakami, koga, tozuka, saegusa;// だ计
	int sum = 0;										// 羆㎝

	cout << "―せだ计ぇ羆だ籔キА\n";
	cout << "1腹だ计";   cin >> yamane;	  sum += yamane;
	cout << "2腹だ计";   cin >> takada;	  sum += takada;
	cout << "3腹だ计";   cin >> kawakami; sum += kawakami;
	cout << "4腹だ计";   cin >> koga;	  sum += koga;
	cout << "5腹だ计";   cin >> tozuka;	  sum += tozuka;
	cout << "6腹だ计";   cin >> saegusa;  sum += saegusa;

	cout << "羆だ琌" << sum << "だ\n";
	cout << "キА琌" << double(sum) / 6 << "だ\n";

	return 0;
}
