// 詢問名字並打招呼 (字串的讀入和顯示)

#include <iostream>
using namespace std;

int main()
{
	char name[40];

	cout << "您的名字是：";
	cin >> name;

	cout << "您好!" << name << "先生!!\n";

	return 0;
}
