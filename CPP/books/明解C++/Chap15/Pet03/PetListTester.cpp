// 繼承版寵物線型清單類別PetList的使用範例

#include <iostream>
#include "PetList.h"
using namespace std;

enum Menu {
	Terminate, AddFirst, AddLast, DspFirst, DspLast, RmvFist, RmvLast, Clear,
	Print, Intro, MenuOver
};

//--- 輸入資料 ---//
Pet* Read()
{
	int    kind;		// 種類
	Pet* ptr;			// 寵物

	do {
		cout << "種類【0…狗／1…貓／2…猴】：";
		cin >> kind;
	} while (kind < 0 || kind > 2);
	switch (kind) {
	 case 0 : ptr = new Pdog();		break;		// 產生狗
	 case 1 : ptr = new Pcat();		break;		// 產生貓 
	 case 2 : ptr = new Pmonkey();	break;		// 產生猴
	}
	ptr->Input();			// 讀取資料
	return ptr;
}

//--- 選擇選單 ---//
Menu SelectMenu()
{
	int ch;

	do {
		cout << "(1) 插入至前端  (2) 插入至尾端  "
			 << "(3) 顯示前端  (4) 顯示尾端\n";
		cout << "(5) 刪除前端    (6) 刪除尾端    "
			 << "(7) 刪除全部  (8) 顯示全部\n";
		cout << "(9) 自我介紹　  (0) 結束：";
		cin >> ch;
	} while (ch < Terminate || ch >= MenuOver);
	return Menu(ch);
}

int main()
{
	Menu	menu;
	PetList	list;

	do {
		menu = SelectMenu();
		switch (menu) {
		 PetNode* p;
		 case AddFirst: {				               // 將節點插入到前端
				cout << "請輸入要插入到前端的資料。\n";
				Pet* x = Read();
				list.AddFirst(x);
			         } break;

		 case AddLast: {			                   // 將節點插入到尾端
				cout << "請輸入要插入到尾端的資料。\n";
				Pet* x = Read();
				list.AddLast(x);
			         } break;

		 case DspFirst: if (p = list.Top())		        	// 顯示前端的節點
				((Pet*)*p)->Sintro(); break;

		 case DspLast: if (p = list.Bottom())		        // 顯示尾端的節點
				((Pet*)*p)->Sintro(); break;

		 case RmvFist: list.RemoveFirst(); break;	        // 刪除前端節點

		 case RmvLast: list.RemoveLast(); break;		    // 刪除尾端節點

		 case Clear: list.Clear();  break;		            // 刪除所有節點

		 case Print	: cout << list;  break;			        // 輸出所有資料

		 case Intro: list.Introduce(); break;		        // 自我介紹
		}
	} while (menu != Terminate);

	return 0;
}
