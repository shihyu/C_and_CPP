// 堆疊抽象類別範本Stack的使用範例（其１）

#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
	Stack<int>* s = new VecStack<int>;

	while (1) {
		int menu;
		cout << "(1)推入  (2)彈出　(0)結束：";
		cin >> menu;
		if (menu == 0) break;

		switch (menu) {
		 int x;
		 case 1: cout << "資料：";
				 cin >> x;
				 s->Push(x);
				 break;

		 case 2: try {
					x = s->Pop();
				 	cout << "彈出的資料為" << x << "。\n"; 
				 }
				 catch (Stack<int>::EmptyErr) {
					cout << "\a堆疊為空的。\n";
				 }
				 break;
		 }
	}

	return 0;
}
