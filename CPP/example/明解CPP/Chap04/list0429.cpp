// 顯示所選擇之動物的叫聲

#include <iostream>
using namespace std;

int main()
{
	enum animal { Dog, Cat, Monkey, Invalid };

	int type;
	do {
		cout << "0…狗 1…貓 2…猴 3…結束：";
		cin >> type;
	} while (type < Dog	|| type > Invalid);

	if (type != Invalid) {
		animal selected = animal(type);
		switch (selected) {
		 case Dog	 : cout << "汪汪!!\n";	break;
		 case Cat	 : cout << "喵喵!!\n";	break;
		 case Monkey : cout << "吱吱!!\n";	break;
		}
	}

	return 0;
}
