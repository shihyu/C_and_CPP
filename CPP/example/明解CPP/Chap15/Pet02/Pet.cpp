// 寵物類別Pet（第2版：實作部分）

#include <string>
#include <iostream>
#include "Pet.h"
using namespace std;

//--- Pet::往輸出串流的插入運算子 ---//
ostream& operator<<(ostream& s, const Pet& p)
{
	return s << "{ " << p.Name() << " }";
}

//--- Pdog::往輸出串流的插入運算子 ---//
ostream& operator<<(ostream& s, const Pdog& p)
{
	return s << "{ 狗, " << p.Name() << ", [" << p.Type() << "] }";
}

//--- Pcat::往輸出串流的插入運算子 ---//
ostream& operator<<(ostream& s, const Pcat& p)
{
	return s << "{ 貓, " << p.Name() << " }";
}

//--- Pmonkey::往輸出串流的插入運算子 ---//
ostream& operator<<(ostream& s, const Pmonkey& p)
{
	return s << "{ 猴, " << p.Name() << ", " << p.Age() << "歲 }";
}
