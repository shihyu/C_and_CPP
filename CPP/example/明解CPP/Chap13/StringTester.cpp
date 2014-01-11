// string的使用範例

#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	string s1 = "ABC";
	string s2 = "HIJKLMN";
	string digits = "0123456789";
	string x1, x2;
	char p[12];

	s1 += "DEF";		// 在s1中加入"DEF"
	s1 += 'G';			// 在s1中加入'G'		
	s1 += s2;			// 在s1中加入"HIJKLMN"	
	s1.insert(6, digits.substr(5, 3));		// 在s1[6]中插入"567"

	s2.replace(3, 2, "kl");	// 將s2[3]∼s2[4]轉換為"kl"
	s2.erase(6);			// 將s2[6]刪除

	strcpy(p, digits.c_str());	// 將digits轉換為Ｃ字串並複製

	cout << "s1 = ";
	for (int i = 0; i < s1.length(); i++)
		cout << s1[i];
	cout << '\n';

	cout << "s2 = " << s2 << '\n';

	cout << "p = " << p << '\n';

	cout << "字串x1 = ";  cin >> x1;
	cout << "字串x2 = ";  cin >> x2;

	string::size_type d = x1.find(x2);		// 從x1中尋找x2
	cout << "字串x1之中" << 
				((d == string::npos) ? "沒有包含x2。\n" : "包含了x2。\n");

	return 0;
}
