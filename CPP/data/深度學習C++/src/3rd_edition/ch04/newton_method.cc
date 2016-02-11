#include <iostream>
#include <cmath>          

using namespace std ;

int main() {
    
    // 利用牛頓迭代法計算根號 x 之值, 計算誤差為 1.0E-6
    // 
    const double  SMALL = 1.0E-6 ;
    double  a , b , n , error ;
    
    cout << "> 輸入數值 : " ;
    cin  >> n ;

    // 設定起始值 a    
    a = 10. ;
    do {
        b  = 0.5 * ( a + n / a ) ;  // 牛頓迭代公式
        error =  abs( a - b ) ;     // abs 為絕對值函式
        a = b ;
    } while ( error > SMALL ) ;
    
    cout << "> 根號 " << n << "  = " << b << endl ;

    return 0 ;
    
}
