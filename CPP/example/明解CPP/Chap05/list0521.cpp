// 傳回參照的函數

#include <iostream>
using namespace std;

//--- 傳回指向x的參照 ---//
int& ref()
{
	static int x;	// 靜態生命週期
	return x;
}

int main()
{
	ref() = 5;		// 將值指定給ref()
	cout << "ref() = " << ref() << '\n';

	return 0;
}
