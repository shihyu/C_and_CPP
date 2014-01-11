// 寵物類別Pet（第2版）的使用範例，其二

#include <iostream>
#include "Pet.h"
using namespace std;

int main()
{
	const int max = 10;			// 寵物的最大數量
	int no;				// 寵物的數量
	Pet* MyPet[max];			// 指向寵物的指標之陣列

	cout << "一共有幾隻寵物呢（1～" << max << "）：";
	do {
		cin >> no;
	} while (no < 1 || no > max);						// 變成1≦no≦max

	for (int i = 0; i < no; i++) {						// 輸入資料
		int k;
		do {
			cout << "種類【0…狗／1…貓／ 2…猴】：";
			cin >> k;
		} while (k < 0 || k > 2);

		switch (k) {
		 case 0: MyPet[i] = new Pdog();		break;
		 case 1: MyPet[i] = new Pcat();		break;
		 case 2: MyPet[i] = new Pmonkey();	break;
		}
		MyPet[i]->Input();
	}

	cout << "\n寵物的一覽表\n";					// 一覽表
	for (int i = 0; i < no; i++)
		cout << *MyPet[i] << '\n';

	cout << "\n讓大家作自我介紹。\n";		// 自我介紹
	for (int i = 0; i < no; i++)
		MyPet[i]->Sintro();

	for (int i = 0; i < no; i++)
		delete MyPet[i];

	return 0;
}
