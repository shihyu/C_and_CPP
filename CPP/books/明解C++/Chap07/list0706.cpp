// 使用陣列的字串以及使用指標的字串

#include <iostream>
using namespace std;

int main()
{
	char a[] = "ABC";		// 使用陣列的字串
	char* p  = "xyz";		// 使用指標的字串

	cout << "a = \"" << a << "\"\n";
	cout << "p = \"" << p << "\"\n";

	return 0;
}
