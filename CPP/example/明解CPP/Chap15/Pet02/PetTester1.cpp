// 寵物類別Pet（第2版）的使用範例，其一

#include <iostream>
#include "Pet.h"
using namespace std;

int main()
{
	Pdog spank("Spank", "柴犬");	// 狗（柴犬）
	Pcat michael("Michael");		// 貓
	Pmonkey jiro("Jiro", 7);		// 猴（歲）

	cout << "寵物的資料：\n";		// 一覽表（插入運算子）
	cout << spank << '\n';
	cout << michael << '\n';
	cout << jiro << '\n';

	cout << "\n讓大家作自我介紹。\n";		// 自我介紹（Sintro）
	spank.Sintro();
	michael.Sintro();
	jiro.Sintro();

	return 0;
}
