// 存取向量的元素

#include <vector>
#include <iostream>
using namespace std;

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	vector<int> x(a, a + 5);	// 從陣列中製作向量

	try {
		for (int i = 0; i <= 10; i++) {
			cout << "x[" << i << "] = " << x.at(i) << '\n';
		}
	}
	catch (std::out_of_range){
		cout << "這是不正確的索引。\n";
		return 1;						// 強制結束
	}

	return 0;
}
