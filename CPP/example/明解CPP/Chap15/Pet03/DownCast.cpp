// 使用dynamic_cast運算子來向下轉型的範例

#include <iostream>
#include "Pet.h"
using namespace std;

//--- 只讓小狗作自我介紹 ---//
void dog_intro(Pet* p)
{
	Pdog* d = dynamic_cast<Pdog*>(p);

	if (d)				// 只在轉型成功的時候
		d->Sintro();		// 自我介紹
}

int main()
{
	Pet* p1 = new Pdog("Spank", "柴犬");			// 狗
	Pet* p2 = new Pcat("Michael");			// 貓

	dog_intro(p1);
	dog_intro(p2);

	delete p1;
	delete p2;

	return 0;
}
