// 弄ninzuだ计陪ボ羆だ籔キА

#include <iostream>
using namespace std;

int main()
{
	const int ninzu = 6;	// 计
	int tensu[ninzu];		// ninzuだ计
	int sum = 0;			// 羆㎝

	cout << "―" << ninzu << "だ计ぇ羆だ籔キА\n";
	for (int i = 0; i < ninzu; i++) {
		cout << i + 1 << "腹だ计";
		cin >> tensu[i];		//弄tensu[i]
		sum += tensu[i];		//盢tensu[i]sum 
	}

	cout << "羆だ琌" << sum << "だ\n";
	cout << "キА琌" << double(sum) / ninzu << "だ\n";

	return 0;
}
