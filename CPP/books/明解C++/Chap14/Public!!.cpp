// public衍生

#include "Base.h"

class Derived : public Base {
	void f() {
		pri = 1;	// 無法存取
		pro = 1;
		pub = 1;
	}
};

int main()
{
	Derived x;

	x.pri = 1;		// 無法存取
	x.pro = 1;		// 無法存取
	x.pub = 1;

	return 0;
}
