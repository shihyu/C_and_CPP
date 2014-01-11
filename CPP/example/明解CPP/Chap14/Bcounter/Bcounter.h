// 案计癘计摸Bcounter

#if !defined(___Class_Bcounter)
	#define	 ___Class_Bcounter

#include "Counter.h"

//===== 案计癘计摸 =====//
class Bcounter : private Counter {

public:
	Bcounter() { }					// 篶

	using Counter::Value;			// 秸俱Θㄧ计舦

	void Increment() {				// Ω﹚竡Θㄧ计
		if (Value() < UINT_MAX - 1) {
			Counter::Increment();
			Counter::Increment();
		}
	}
};

#endif
