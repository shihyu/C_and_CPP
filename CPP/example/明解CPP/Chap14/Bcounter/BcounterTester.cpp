// 偶數增加次數類別Bcounter的使用範例

#include <iostream>
#include "Bcounter.h"
using namespace std;

int main()
{
	int n;
	Bcounter cnt;

	cout << "增加了多少次呢：";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cnt.Increment();
		cout << cnt.Value() << ' ';
	}
	cout << '\n';

	return 0;
}
