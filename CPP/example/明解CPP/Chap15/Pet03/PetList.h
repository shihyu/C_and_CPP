// 繼承版寵物線型清單類別PetList（介面部份）

#if !defined(___Class_PetList)
	#define	 ___Class_PetList

#include <iostream>
#include "Pet.h"
using namespace std;

//===== 寵物節點類別 =====//
class PetNode {
	friend class PetList;

	Pet*	 pet;			// 資料
	PetNode* next;			// 後續指標（指向後續節點的指標）

public:
	PetNode(Pet* p, PetNode* n = NULL) : pet(p), next(n) { } // 建構子
   ~PetNode()		{ delete pet; }		// 解構子

	PetNode* Next()	{ return next; }	// 後續節點
	operator Pet*()	{ return pet;  }	// 轉換函數
};

//===== 寵物線型清單類別（PetNode的friend類別） =====//
class PetList {
	friend ostream& operator<<(ostream& s, const PetList& x);

	PetNode* top;			// 指向前端節點的指標
	PetNode* dummy;			// 指向假節點的指標

	PetList(const PetList&);			// 讓複製建構子無效化
	PetList& operator=(const PetList&);	// 讓指定運算子無效化

public:
	PetList();					// 建構子
                ~PetList();				// 解構子

	PetNode* Top() { return (top == dummy) ? NULL : top; }	// 前端節點
	PetNode* Bottom();					// 尾端節點

	PetList& AddFirst(Pet*);		// 將節點插到前端
	PetList& AddLast(Pet*);			// 將節點插到尾端
	PetList& RemoveFirst();			// 刪除前端節點
	PetList& RemoveLast();			// 刪除尾端節點
	PetList& Clear();				// 刪除所有節點

	PetList& Introduce();			// 自我介紹
};

ostream& operator<<(ostream&, const PetList&);

#endif
