// 使用陣列的字串以及使用指標的字串

#include <iostream>
using namespace std;

int main()
{
	char a[][6] = {"S5000", "V8", "W140"};		// 使用陣列的字串之陣列
	char* p[]   = {"12345", "A8", "abcd"};		// 使用指標的字串之陣列

	for (int i = 0; i < 3; i++)
		cout << "a[" << i << "] = \"" << a[i] << "\"\n";

	for (int i = 0; i < 3; i++)
		cout << "p[" << i << "] = \"" << p[i] << "\"\n";

	return 0;
}
