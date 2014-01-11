// ―眔皚ぇ程(ㄏノ更)

#include <iostream>
using namespace std;

//--- 肚じ计n皚xぇ程(int篈) ---//
int maxof(const int x[], int n)
{
	int max = x[0];
	for (int i = 1; i < n; i++)
		if (x[i] > max)
			max = x[i];
	return max;
}

//--- 肚じ计n皚xぇ程(double篈) ---//
double maxof(const double x[], int n)
{
	double max = x[0];
	for (int i = 1; i < n; i++)
		if (x[i] > max)
			max = x[i];
	return max;
}

int main()
{
	const int isize = 8;
	int ix[isize];

	// 俱计皚程
	cout <<"叫块"<< isize << "俱计\n";
	for (int i = 0; i < isize; i++) {
		cout << i + 1 << ":";
		cin >> ix[i];
	}
	cout << "程" << maxof(ix, isize) << "\n\n";

	const int dsize = 5;
	double dx[dsize];

	// 龟计皚程
	cout <<"叫块"<< dsize << "龟计\n";

	for (int i = 0; i < dsize; i++) {
		cout << i + 1 << ":";
		cin >> dx[i];
	}
	cout << "程" << maxof(dx, dsize) << "\n";

	return 0;
}
