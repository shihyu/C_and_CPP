// 堆疊 類別範本Stack的使用範例（反轉字串）

#include <string>
#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
	string x;

	cout << "字串：";
	cin >> x;

	Stack<char> s(x.length());		// 堆疊s的容量為字串x的長度

	try {
		for (int i = 0; i < x.length(); i++) // 從開頭文字開始依序推入
			s.Push(x[i]);

		for (int i = 0; i < x.length(); i++)  {
			char c = s.Pop();	           	 // 彈出（可以逆向得到）
			cout << c;
		}
		cout << '\n';
	}
	catch (Stack<char>::OverflowErr x) {
		cout << "\a想要對已滿的<char>堆疊[" << x.vec()
			 << "]進行推入。\n";
	}
	catch (Stack<char>::EmptyErr x) {
		cout << "\a想要從空的<char>堆疊[" << x.vec()
			 << "]進行彈出。\n";
	}

	return 0;
}
