// 顯示程式名稱、程式參數 (其二)

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int i = 0;
	while (argc-- > 0)
		cout << "argv[" << i++ << "] = " << *argv++ << '\n';
	return 0;
}
