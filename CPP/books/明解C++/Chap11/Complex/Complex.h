// 複數類別Complex

#if !defined(___Class_Complex)
	#define  ___Class_Complex

#include <iostream>
using namespace std;

//===== 複數類別 =====//
class Complex {
	double re;		// 實的部分
	double im;		// 虛的部分

public:
	Complex(double r = 0, double i = 0) : re(r), im(i) { }	// 建構子

	double Real() const { return re; }	// 傳回實的部分
	double Imag() const { return im; }	// 傳回虛的部分

	Complex operator+() { return *this; }				// 一元運算子+
	Complex operator-() { return Complex(-re, -im); }	// 一元運算子-

	// +=運算子
	Complex& operator+=(const Complex& x) {
		re += x.re;
		im += x.im;
		return *this;
	}

	// -=運算子
	Complex& operator-=(const Complex& x) {
		re -= x.re;
		im -= x.im;
		return *this;
	}

	friend bool operator==(const Complex& x, const Complex& y) {  // ==運算子
		return x.re == y.re && x.im == y.im;
	}

	friend bool operator!=(const Complex& x, const Complex& y) {  // !=運算子
		return !(x == y);
	}

	// Complex + Complex
	friend Complex operator+(const Complex& x, const Complex& y) {
		return Complex(x.re + y.re, x.im + y.im);
	}

	// double + Complex
	friend Complex operator+(double x, const Complex& y) {
		return Complex(x + y.re, y.im);
	}

	// Complex + double
	friend Complex operator+(const Complex& x, double y) {
		return Complex(x.re + y, x.im);
	}
};

inline ostream& operator<<(ostream& s, Complex& x)
{
	return s << '(' << x.Real() << ", " << x.Imag() << ')';
}

#endif
