// 盢弄俱计羆 (ぃ羆璽)

#include <iostream>
using namespace std;

int main ()
{
	int n;			// 羆计
	cout << "盢俱计羆\n";
	cout << "璶羆碭俱计";
	cin >> n;

	int sum = 0;		//羆㎝
	for (int i = 0; i < n; i++) {
		int t;
		cout << "俱计";
		cin >> t;
		if (t < 0) {
			cout << "\a璽计ぃ秈︽羆\n";
			continue;
		}
		sum += t;
	}
	cout << "羆㎝" << sum << "\n";

	return 0;
}
