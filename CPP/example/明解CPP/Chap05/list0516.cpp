// 顯示無符號整數的邏輯積、邏輯和、邏輯差 (互斥的邏輯和)、1的補數

#include <iostream>
using namespace std;

//--- 求取整數x中的"1 "的位元數 ---//
int count_bits(unsigned x)
{
	int bits = 0;
	while (x) {
		if (x & 1U) bits++;
		x >>= 1;
	}
	return bits;
}

//--- 求取unsigned型態的位元數 ---//
int int_bits()
{
	return count_bits(~0U);
}

//--- 顯示unsigned型態的位元結構 ---//
void print_bits(unsigned x)
{
	for (int i = int_bits() - 1; i >= 0; i--)
		cout << ((x >> i) & 1U) ? '1' : '0';
}

int main()
{
	unsigned a, b;

	cout << "輸入兩個非負數的整數。\n";
	cout << "a：";	  cin >> a;
	cout << "b：";	  cin >> b;

	cout << "a   　= ";  print_bits(a);		cout << '\n';
	cout << "b   　= ";  print_bits(b);		cout << '\n';
	cout << "a & b = ";  print_bits(a & b);	cout << '\n';	//邏輯積
	cout << "a | b = ";  print_bits(a | b);	cout << '\n';	//邏輯和
	cout << "a ^ b = ";  print_bits(a ^ b);	cout << '\n';	//邏輯差
	cout << "~a　  = ";  print_bits(~a);	cout << '\n';	//1的補數 
	cout << "~b　  = ";  print_bits(~b);	cout << '\n';	//1的補數

	return 0;
}
