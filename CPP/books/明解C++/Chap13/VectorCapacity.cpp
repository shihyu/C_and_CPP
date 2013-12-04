// vector的元素數與容量

#include <vector>
#include <iostream>
using namespace std;

int main()
{
	vector<int> x;
	cout << "容量：" << x.capacity() << '\n';
	x.reserve(7);		// 使容量最少也有7

	x.push_back(15);	x.push_back(92);
	x.push_back(75);	x.push_back(48);

	cout << "容量：" << x.capacity() << '\n';

	for (int i = 0; i < x.size(); i++)
		cout << "x[" << i << "] = " << x[i] << '\n';

	return 0;
}
