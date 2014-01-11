// 偶數記數類別Bcounter

#if !defined(___Class_Bcounter)
	#define	 ___Class_Bcounter

#include "Counter.h"

//===== 偶數記數類別 =====//
class Bcounter : private Counter {

public:
	Bcounter() { }					// 建構子

	using Counter::Value;			// 調整成員函數的存取權限

	void Increment() {				// 再次定義成員函數
		if (Value() < UINT_MAX - 1) {
			Counter::Increment();
			Counter::Increment();
		}
	}
};

#endif
