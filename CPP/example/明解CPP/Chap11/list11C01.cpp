// 初始化與指定/傳值與傳址的驗證

#include <iostream>
using namespace std;

//===== 用來驗證的類別 =====//
class Test {
public:
	Test() {					      	// 預設建構子
		 cout << "初始化：Test()\n";
	}

	Test(const Test& t) {				// 複製建構子
		cout << "初始化：Test(const Test&)\n";
	}

	Test& operator=(const Test& t) {	// 指定運算子
		cout << "指定：Test = Test\n"; return *this;
	}
};

//--- 傳值 ---//
void value(Test a) { }

//--- 傳址 ---//
void reference(Test& a)  { }

int main()
{
	Test x;
	Test y = x;
	Test z(x);
	y = x;
	value(x);
	reference(x);
	return 0;
}
