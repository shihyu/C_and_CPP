// 以讀入的個數來顯示*

#include <iostream> 
using namespace std;

int main ()
{
	int n;
	cout << "要顯示幾個*：";
	cin >> n;

	int i = 0;
	while (i < n) {
		cout << '*';
		i++;
	}
	cout << '\n';

	return 0;
}
