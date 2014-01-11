// 寵物類別Pet（第１版：實作部分）

#include <string>
#include <iostream>
#include "Pet.h"
using namespace std;

//--- 讀入 ---//
void Pet::Input()
{
	int k;
	do {
		cout << "種類【0…狗／1…貓／ 2…猴】：";
		cin >> k;
	} while (k < Dog || k > Monkey);
	kind = PetType(k);
	cout << "名稱：";
	cin >> name;
}

//--- 自我介紹 ---//
void Pet::Sintro() const
{
	cout << "我是";
	switch (kind) {
	 case Dog :    cout << "狗"; break;
	 case Cat :	   cout << "貓"; break;
	 case Monkey : cout << "猴"; break;
	}
	cout << "，我的名字叫做" << name << "!!\n";
}

//--- 往輸出串流的插入運算子 ---//
ostream& operator<<(ostream& s, const Pet& p)
{
	s << "{ ";
	switch (p.Type()) {
	 case Pet::Dog    : s << "狗, "; break;
	 case Pet::Cat    : s << "貓, "; break;
	 case Pet::Monkey : s << "猴, "; break;
	}
	s << p.Name() << " }";
	return s;
}
