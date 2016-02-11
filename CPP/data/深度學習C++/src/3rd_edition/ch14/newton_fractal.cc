#include <iostream>
#include <complex>    
#include <cmath>      
#include <fstream>

using namespace std ;

// 函數函式     :  z^3 - 1
template <class T>  
T  f( const T& z ) {  return z * z * z - 1. ; }

// 函數微分函式 :  3 z^2 
template <class T>
T  df( const T& z ) { return  3. * z * z ;  }


// 使用牛頓法求根
template < class T >
T  find_root( T a ) {

    T       b ;
    double  dz ; 
    const double TOL  = 1.0e-10 ;

    do {
        b = a - f(a) / df(a) ;       // 牛頓迭代公式
        dz = abs(b-a) ;              // 計算新舊值差距
        a = b ;                      // 更新數值
    } while ( dz > TOL ) ;
    
    return a ;

}


int main() {

    const double  TOL2 = 1.0e-7 ;
    const double  PI = 4. * atan(1) ;
    const int     N = 3 ;

    int     i , j , k ;
    double  x , y , dx , dy , norm ;
    double  n , a , b , c , d ;

    complex<double>  z , rt ;

    // F(z) = z^3 - 1 的三個根
    complex<double>  root[N] = { 
            complex<double>(1,0) , 
            complex<double>(cos(2.*PI/3),sin(2.*PI/3)) ,
            complex<double>(cos(4.*PI/3),sin(4.*PI/3)) } ;

    // 依據迭代法的收斂值儲存起始位置
    ofstream  rt1("rt1") , rt2("rt2") , rt3("rt3") ;
    
    // 起始位置的方塊範圍 : (a,b) 左下角座標   (c,d) 右上角座標
    a = b = -1 ;   
    c = d = 1 ;

    // 平均間格數
    n = 100 ;                 

    // x 與 y 的間距
    dx = (c-a)/n ;           
    dy = (d-b)/n ;           

    
    // 對方塊範圍內的每個點迭代
    for ( i = 0 ; i <= n ; ++i ) {
        for ( j = 0 ; j <= n ; ++j ) {

            // 計算起始點座標
            x = a + i * dx ;
            y = b + j * dy ;
            
            // 轉成複數點
            z = complex<double>(x,y) ;

            // 以牛頓法求根
            rt = find_root(z) ;

            // 判斷數值根為哪一個根
            for ( k = 0 ; k < N ; ++k ) {

                norm = abs(rt-root[k]) ;

                if ( norm <= TOL2 ) {
                    if ( k == 0 ) 
                        rt1 << x << "  " << y << "\n" ;
                    else if ( k == 1 ) 
                        rt2 << x << "  " << y << "\n" ;
                    else 
                        rt3 << x << "  " << y << "\n" ;
                    break ;
                }
            }

        }

    }

    return 0 ;
    
}
