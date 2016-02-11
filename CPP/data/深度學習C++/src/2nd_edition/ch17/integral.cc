#include <iostream>
#include <math.h>
#include <functional>

using namespace std ;

// 定義 X 平方, 立方與 Sin 函數
struct  Square {
    double  operator()( double x ) const { return x * x ; }
};

template <typename T>
T  Cubic ( T x ) { return x * x * x ; }

template <typename T>
double Sin( T x ) { return sin(x) ; }


// 計算函數 fn 在 [a,b] 區間的定積分, 
// 積分以切割為 n 個平均等份的長條形面積計算
//
template <typename Function>
double  integral( Function fn , double a , double b , 
                  int n = 1000000 ) {

    double  area = 0.  ;
    double  dx = ( b - a ) / n ;

    for ( int i = 0 ; i < n ; ++i ) area += fn(a+dx*i) ;
    
    return  dx * area ;
}


// 計算函數 fn 在 [a,b] 區間且函數值滿足某個設定條件的定積分, 
// 積分以切割為 n 個平均等份的長條形面積計算
//
template < typename Fn1 , typename Fn2 >
double  integral( Fn1 fn , double a , double b , 
                  const Fn2& fn2 , int n = 1000000 ) {

    double  area = 0. , tmp ;
    double  dx = ( b - a ) / n ;

    for ( int i = 0 ; i < n ; ++i ) {
        tmp = fn(a+dx*i) ;
        if ( fn2(tmp) ) area += tmp ;
    }
    
    return  dx * area ;
}

    
int main() {
    
    const double PI = 3.141592654 ;
    
    // 計算平方函數在 [0,1] 區間的定積分
    cout << "> 平方函數在 [0,1] 區間的定積分 = "
         << integral( Square() , 0 , 1 ) << endl ;

    // 計算平方函數在 [0,1] 且函數值須小於 0.25 的定積分
    cout << "> 平方函數在 [0,1] 且函數值須小於 0.25 的定積分 = " 
         << integral( Square() , 0 ,  1, 
                      bind2nd( less<double>() , 0.25 ) ) << endl ;

    // 計算立方函數在 [0,1] 區間的定積分
    cout << "> 立方函數在 [0,1] 區間的定積分 = "
         << integral( Cubic<double> , 0 , 1 ) << endl ;

    // 計算 sin 函數在 [0,PI] 區間的定積分
    cout << "> sin(x) 在 [0,PI] 區間的定積分 = "
         << integral( Sin<double> , 0 , PI ) << endl ;

    // 計算 sin 函數在 [0,PI] 且 sin(x) 須大於零的定積分
    cout << "> sin(x) 在 [0,PI] 且 sin(x) 須大於零的定積分 = " 
         << integral( Sin<double> , 0 , 2*PI , 
                      bind2nd( greater<double>() , 0. ) ) << endl ;

    return 0 ;

}
