#include <iostream>
#include <complex>     // 使用複數模板類別
#include <cmath>       // 提供絕對值函式 abs(x)

using namespace std ;

// 函數函式 : F(X) = X^3 - X^2 + X - 1
template <class T>
T  f( const T& x ) {  return x * x * x - x * x + x - 1. ; }

// 函數微分函式 : 3 X^2 - 2 X + 1
template <class T>
T  df( const T& x ) { return  3. * x * x - 2. * x + 1. ;  }

// 使用牛頓法求根
template < class T >
T  find_root( T x1 ) {

    const double TOL = 1.0e-7 ;

    T       x2 ;
    double  dx ; 

    do {
        x2 = x1 - f(x1) / df(x1) ;     // 牛頓迭代公式
        dx = abs(x2-x1) ;              // 計算新舊值差距
        x1 = x2 ;                      // 更新數值
    } while ( dx > TOL ) ;
    
    return x2 ;

}

int main() {

    double  x ;
    cout << "> 輸入實數起始值 : " ;
    cin >> x ;
    cout << "> 實數根為 : " << find_root(x) << endl ;

    double  re , im ;
    cout << "> 輸入複數起始值 : " ;
    cin >> re >> im ;

    // 定義實數與虛數部份皆為雙精確度浮點數的複數物件
    complex<double> c(re,im) ;
    cout << "> 複數根為 : " << find_root(c) << endl ;

    return 0 ;
    
}

