#include <iostream>
#include <cmath>
#include <numeric>

using namespace std ;

// 先加後減運算或者是先減後加運算, 預設為先加後減運算
template <class T>
struct  plus_minus {
    int  sign ;
    plus_minus( int s = 1 ) : sign(s) {}
    T  operator() ( const T& a , const T& b ) {
        T  sum = ( sign > 0 ? ( a + b ) : ( a - b ) ) ;
        sign *= -1 ;
        return  sum ;
    }
};

// 先減後加運算
template <class T>
T  minus_plus( const T& a , const T& b ) {
    static int sign = 1 ;
    T  sum = ( sign > 0 ? a + b : a - b ) ;
    sign *= -1 ;
    return  sum ;
}

int main() {

    int a[5] = { 2 , 2 , 1 , 1 , 1 };
    int b[5] = { 1 , 2 , 0 , 1 , 2 };
    
    // 計算  0 + a[0]b[0] + a[1]b[1] + ... + a[4]b[4] 之值
    cout << inner_product(a,a+5,b,0) << endl ;

    // 計算  v + a[0]b[0] - a[1]b[1] + ... - a[4]b[4] 之值
    int  v = 10 ;
    cout << inner_product(a,a+5,b,v,plus_minus<int>(),multiplies<int>()) 
         << endl ;
    
    // 計算  0 - a[0]b[0] + a[1]b[1] - ... + a[4]b[4] 之值
    cout << inner_product(a,a+5,b,0,plus_minus<int>(-1),multiplies<int>())
         << endl ;
    
    // 計算  8 - a[0]b[0] + a[1]b[1] - ... + a[4]b[4] 之值
    cout << inner_product(a,a+5,b,8,minus_plus<int>,multiplies<int>()) 
         << endl ;    

    // 計算  a 向量的長度
    // sqrt( 0 + a[0]a[0] + a[1]a[1] + ... + a[4]a[4] )
    cout << sqrt(static_cast<double>(inner_product(a,a+5,a,0))) << endl ;

    return 0 ;
    
}
