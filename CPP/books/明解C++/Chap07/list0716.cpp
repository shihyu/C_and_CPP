// 函數strcpy的使用範例 (善加使用被傳回的指標)

#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	char tmp[100];
	char s1[100], s2[100], s3[100];

	cout << "字串：";
	cin >> tmp;

	// 將複製到s1的字串也複製到s2
	strcpy(s1, strcpy(s2, tmp));	

	cout << "s1 = \"" << s1 << "\"\n";
	cout << "s2 = \"" << s2 << "\"\n";
	cout << "s3 = \"" << strcpy(s3, tmp) << "\"\n";

	return 0;
}
