// 顯示字元和字元碼

#include <cctype>
#include <climits>
#include <iostream>
using namespace std;

int main()
{
	cout << "此處理器的字元和字元碼\n";
	for (char i = 0; ; i++) {
		switch (i) {
		 case '\a' : cout << "\\a";  break;
		 case '\b' : cout << "\\b";  break;
		 case '\f' : cout << "\\f";  break;
		 case '\n' : cout << "\\n";  break;
		 case '\r' : cout << "\\r";  break;
		 case '\t' : cout << "\\t";  break;
		 case '\v' : cout << "\\v";  break;
		 default   : cout << ' ' << (isprint(i) ? i : ' '); 
		}
		// 轉型為整數型態後以十六進位顯示
		cout << ' ' << hex << int(i) << '\n';
		if (i == CHAR_MAX) break;
	}
	return (0);
}
