// 顯示選擇的動物之叫聲 (指向函數的指標) 

#include <iostream>
using namespace std; 

enum animal { Dog, Cat, Monkey, Invalid };

//--- 狗 ---//
void dog()
{
	cout << "汪汪!!\n";
}

//--- 貓 ---//
void cat()
{
	cout << "喵!!\n";
}

//--- 猴 ---//
void monkey()
{
	cout << "吱吱!!\n";
}

//--- main ---//
int main()
{
	typedef void (*afunc)();
	afunc fn[] = {dog, cat, monkey};
	int menu;

	do {
		do {
			cout << "0…狗　1…貓　2…猴　3…結束：";
			cin >> menu;
		} while (menu < Dog	|| menu > Invalid);
		if (menu != Invalid)
			fn[menu]();
	} while (menu != Invalid);

	return 0;
}
