//  求取兩值之最大值的函數範本

#include <cstring>
#include <iostream>
using namespace std;

//--- 求取a, b的較大一方的值 ---//	 
template <class Type> Type maxof(Type a, Type b)
{
	return a > b ? a : b;
}

//--- 求取a, b的較大一方的值 ( const char*型態的特殊化 )
template <> const char* maxof<const char*>(const char* a, const char* b)
{
	return strcmp(a, b) > 0 ? a : b;
}

int main()
{
	int a, b;
	double x;
	char s[100], t[100];

	cout << "整數a：";	  cin >> a;
	cout << "整數b：";	  cin >> b;
	cout << "實數x：";	  cin >> x;
	cout << "字串s：";            cin >> s;
	cout << "字串t：";             cin >> t;

	cout << "a與b的較大一方的值為" << maxof(a, b)              << "。\n";
	cout << "a與x的較大一方的值為" << maxof<double>(a, x)      << "。\n";
	cout << "s與t的較大一方的值為" << maxof<const char*>(s, t) << "。\n";

	return 0;
}
