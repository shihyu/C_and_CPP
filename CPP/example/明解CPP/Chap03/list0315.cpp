// 盢弄俱计羆 (羆㎝ぃ禬筁1000絛瞅ず秈︽羆)

#include <iostream>
using namespace std;

int main ()
{
	int n;			// 羆计
	cout << "盢俱计羆\n";
	cout << "璶羆碭俱计";
	cin >> n;

	int sum = 0;		// 羆㎝
	for (int i = 0; i < n; i++) {
		int t;
		cout << "俱计";
		cin >> t;
		if (sum + t > 1000) {
			cout << "\a羆㎝禬筁1000\n礚跌程计\n";
			break; 
		}
		sum += t;
	}
	cout << "羆㎝" << sum << "\n";

	return 0;
}
