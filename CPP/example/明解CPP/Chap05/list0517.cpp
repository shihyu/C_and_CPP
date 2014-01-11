// 顯示將無符號整數型態左右位移之後的值

#include <iostream>
using namespace std;

int count_bits(unsigned x){
    int bits = 0;
	while (x) {
		if (x & 1U) bits++;
		x >>= 1;
	}
	return bits;
 }

int int_bits(){
	return count_bits(~0U);
}

void print_bits(unsigned x){
	for (int i = int_bits() - 1; i >= 0; i--)
		cout << ((x >> i) & 1U) ? '1' : '0';
}

int main()
{
	unsigned x, n;

	cout << "非負數的整數：";			cin >> x;
	cout << "位移的位元數：";	cin >> n;

	cout << "整數　 = ";  print_bits(x);		 cout << '\n';
	cout << "左位移 = ";  print_bits(x << n);	 cout << '\n';
	cout << "右位移 = ";  print_bits(x >> n);	 cout << '\n';

	return 0;
}
