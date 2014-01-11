// 送出與捕捉例外

#include <new>
#include <iostream>
using namespace std;

//=== 溢位類別 ===//
class OverFlow { };

//--- 傳回x的2倍的值 ---//
int f(int x)
{
	if (x < 0)
		throw "奇怪，值竟然變成負數了。\n";
	else if (x > 30000)
		throw OverFlow();
	else
		return 2 * x;
}

int main()
{
	int a;
	cout << "整數：";
	cin >> a;

	try {
		int b = f(a);
		cout << "該數的2倍為" << b << "。\n";
	}
	catch (const char* str) {		// 捕捉字串的例外
		cout << "發生例外：" << str;
	}
	catch (OverFlow) {				// 在這裡捕捉到了OverFlow型態的例外
		cout << "發生溢位了，程式結束。\n";
		return 1;
	}
	return 0;
}
