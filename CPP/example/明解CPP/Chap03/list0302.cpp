// 視讀入的值來顯示猜拳的手勢 (只接受0、1、2)

#include <iostream>
using namespace std;

int main ()
{
	int hand;

	do {
		cout << "請選擇手勢 (0…石頭／1…剪刀／2…布)：";
		cin >> hand;
	} while (hand < 0 || hand > 2);

	switch (hand) {
	 case 0: cout << "石頭\n";	  break;
	 case 1: cout << "剪刀\n";   break;
	 case 2: cout << "布\n";	  break;
	}

	return 0;
}
