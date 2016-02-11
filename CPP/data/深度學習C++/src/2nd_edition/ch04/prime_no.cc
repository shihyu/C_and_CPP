#include <iostream>
#include <cmath>               // 使用 sqrt 計算平方根

using namespace std ;

int main() {

    int  i , n , sqrtn ;
    bool is_prime_number ;

    while ( 1 ) {
        
        cout << "> 請輸入一正整數 ( 輸入負數結束程式 ) : " ;
        cin >> n ;

        if ( n < 0 ) {
            // 輸入負數提早離開 while 迴圈
            break ;
        } else if ( n <= 1 ) {
            // 輸入的數字 <= 1
            cout << "> 輸入的數字必須為大於 1 的自然數\n\n" ;
            continue ;
        } else if ( n == 2 ) {
            // 輸入的數字為 2, 2 為質數
            is_prime_number = true ;
        } else if ( n % 2 == 0 ) {
            // 輸入的數字為偶數, 則此數不是質數
            is_prime_number = false ;
        } else {
            // 輸入的數字為大於 2 的奇數
            is_prime_number = true ;
            sqrtn = static_cast<int>( sqrt( n * 1.0 ) ) ;
            
            for ( i = 3 ; i <= sqrtn ; ++i ) {
                if ( n % i == 0 ) {
                    // 若 i 為 n 的因數, 則 n 不是質數, 
                    // 使用 break 提早脫離迴圈
                    is_prime_number = false ;
                    break ;         
                }
            }
        }
        cout << "> " << n << ( is_prime_number ? " 是" : " 不是" ) 
             << "質數\n\n" ;

    }

    return 0 ;
    
}
