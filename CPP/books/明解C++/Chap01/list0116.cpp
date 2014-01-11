// 字串的初始化和指定

#include <string>
#include <iostream>
using namespace std;

int main()
{
	string s1 = "ABC";		// 初始化
	string s2 = "XYZ";		// 初始化
	s1 = "FBI";				// 指定 (將值改寫)

	cout << "字串s1是" << s1 << "\n";		// 顯示
	cout << "字串s2是" << s2 << "\n";		// 顯示

	return 0;
}
