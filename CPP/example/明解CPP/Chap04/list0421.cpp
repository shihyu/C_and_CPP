// 弄せだ计陪ボ羆だ籔キА

#include <iostream>
using namespace std;

int main()
{
	int tensu[6];		// せだ计
	int sum = 0;		// 羆㎝

	cout << "―せだ计ぇ羆だ籔キА\n";
	for (int i = 0; i < 6; i++) {
		cout << i + 1 << "腹だ计";
		cin >> tensu[i];		// 弄tensu[i]
		sum += tensu[i];		// 盢tensu[i]sum 
	}

	cout << "羆だ琌" << sum << "だ\n";
	cout << "キА琌" << double(sum) / 6 << "だ\n ";

	return 0;
}
