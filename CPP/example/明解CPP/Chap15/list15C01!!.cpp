class A {
public:
	void f() { / *°K* / }
};

class B : public A {
public:
	virtual void f() { / *°K* / }	                // µÍ¿¿®Áº∆
};

class C : public B {
public:
	void f()	{ / *°K* / }		// µÍ¿¿®Áº∆
	void f(int)	{ / *°K* / }	// ¶h∏¸°]overload°^
};
