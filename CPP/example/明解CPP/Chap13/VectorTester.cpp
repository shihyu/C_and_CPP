// vector的使用範例（讀取不知道其資料數的資料）

#include <vector>
#include <iostream>
using namespace std;

int main()
{
	vector<int> x;

	cout << "請輸入整數。\n※結束為9999。\n";

	while (true) {
		int temp;
		cin >> temp;
		if (temp == 9999) break;
		x.push_back(temp);
	}

	for (int i = 0; i < x.size(); i++)
		cout << "x[" << i << "] = " << x[i] << '\n';

	return 0;
}
