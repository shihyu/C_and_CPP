// 布林值類別Boolean

#if !defined(___Class_Boolean)
	#define  ___Class_Boolean

#include <iostream>
using namespace std;

//===== 布林值類別 =====//
class Boolean {
public:
	enum boolean {False, True};			// False為偽／True為真

private:
	boolean x;		                	// 布林值

public:
	Boolean() : x(False) { }					// 偽
	Boolean(int val) : x((val == 0) ? False : True) { }

	operator int() const    { return x; }		// 轉換函數 int(op)
	operator const char*()	{ return x == False ? "False" : "True"; }
};

inline ostream& operator<<(ostream& s, Boolean& x)
{
	return s << (const char*)x;
}

#endif
