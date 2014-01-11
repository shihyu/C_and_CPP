// 發出警告的函數 (預設引數)

#include <iostream>
using namespace std;

//--- 發出n次的警告 ---//
void alerts(int n = 3)
{
	for (int i = 0; i < n; i++)
		cout << '\a';
}

int main()
{
	alerts();
	cout << "警告！\n";

	alerts(5);
	cout << "再次警告！\n";

	return 0;
}
