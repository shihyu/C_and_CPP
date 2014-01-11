// 顯示程式名稱、程式參數 (其一)

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
		cout << "argv[" << i << "] = " << argv[i] << '\n';
	return 0;
}
