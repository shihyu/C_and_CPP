// 將字串存放到陣列並顯示 (指定)

#include <iostream>
using namespace std;

int main()
{
	char s[4];		// 存放字串的陣列

	s[0] = 'A';		// 指定
	s[1] = 'B';		// 指定
	s[2] = 'C';		// 指定
	s[3] = '\0';  		// 指定

	cout << "指定給陣列s的字串是\"" << s << "\"。\n";		// 顯示

	return 0;
}
