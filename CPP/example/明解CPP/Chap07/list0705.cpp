// 將字串中的小寫字母轉換成大寫字母並顯示

#include <cctype>
#include <iostream>
using namespace std;

//--- 顯示字串s (將小寫字母轉換成大寫字母)---//
void put_upper(const char s[])
{
	int i = 0;
	while (s[i] != 0)
		cout << char(toupper(s[i++]));
}

int main()
{
	char str[40];

	cout << "字串：";
	cin >> str;

	put_upper(str);

	return 0;
}
