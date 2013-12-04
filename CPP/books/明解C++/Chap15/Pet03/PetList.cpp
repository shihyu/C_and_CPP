// 繼承版寵物線型清單類別PetList（實作部份）

#include <iostream>
#include "Petlist.h"
using namespace std;

//--- 建構子 ---//
PetList::PetList()
{
	top = dummy = new PetNode(NULL, NULL);		// 建立假節點
}

//--- 解構子 ---//
PetList::~PetList()
{
	Clear();
	delete top;					// 釋放假節點
}

//--- 搜尋尾端的節點 ---//
PetNode* PetList::Bottom()
{
	if (top == dummy)					// 清單為空白
		return NULL;
	PetNode* ptr = top;					// 找到假節點為止
	while (ptr->next != dummy)				// 走訪所有節點
		ptr = ptr->next;
	return ptr;
}

//--- 將節點插到前面 ---//
PetList& PetList::AddFirst(Pet* x)
{
	PetNode* ptr = top;					// 插入之前的前端節點
	top = new PetNode(x, ptr);
	return *this;
}

//--- 將節點插到尾端 ---//
PetList& PetList::AddLast(Pet* x)
{
	if (top == dummy)					// 若清單為空白的話
		AddFirst(x);				// 以AddFirst來插到前端
	else {
		PetNode* ptr = Bottom();
		ptr->next = new PetNode(x, dummy);
	}
	return *this;
}

//--- 刪除前端的節點 ---//
PetList& PetList::RemoveFirst()
{
	if (top != dummy) {
		PetNode* ptr = top->next;			// 前面算起的第2個節點
		delete top;
		top = ptr;
	}
	return *this;
}

//--- 刪除尾端節點 -----//
PetList& PetList::RemoveLast()
{
	if (top == dummy)					// 若清單為空白的話
		;									
	else if (top->next == dummy)			                // 如果節點不是只有一個
		RemoveFirst();				// 就以RemoveFirst刪除前端節點
	else {
		PetNode* ptr = top;				// 目前節點
		PetNode* pre;				// 目前節點的下一個節點
		while (ptr->next != dummy) {
			pre = ptr;
			ptr = ptr->next;
		}
		pre->next = dummy;			// pre是刪除後的尾端節點
		delete ptr;
	}
	return *this;
}

//--- 刪除所有節點 ---//
PetList& PetList::Clear()
{
	PetNode* ptr = top;
	while (ptr != dummy) {
		PetNode* next = ptr->next;
		delete ptr;
		ptr = next;
	}
	top = dummy;
	return *this;
}

//--- 全員的自我介紹 ---//
PetList& PetList::Introduce()
{
	PetNode* ptr = top;
	cout << "<<---------------- 自我介紹 ---------------->>\n";
	while (ptr != dummy) {
		ptr->pet->Sintro();
		ptr = ptr->next;
	}
	cout << "<<------------------------------------------>>\n";
	return *this;
}

//--- 插入運算子 ---//
ostream& operator<<(ostream& s, const PetList& x)
{
	PetNode* ptr = x.top;
	s << "{\n";
	while (ptr != x.dummy) {
		s << '\t' << *(Pet*)(*ptr) << '\n';
		ptr = ptr->Next();
	}
	s << "}\n";
	return s;
}
