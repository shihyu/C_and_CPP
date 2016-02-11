#include <iostream>

using namespace std ;

int main() {

    int   i , j , k , sum ;
    const int m = 2 , n = 3 ;
    
    // ©w¸q¨â¯x°}¤Î­¼¿n¯x°}
    int a[m][n] = { { 1 , 2 , 1 } , { 2 , 1 , 1 } } ;
    int b[n][m] = { { 1 , 2 } , { 0 , 1 } , { 2 , 2 } } ;
    int c[m][m] ;
    
    // ¬Û­¼
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
            sum = 0 ;
            for ( k = 0 ; k < n ; ++k ) sum += a[i][k] * b[k][j] ;
            c[i][j] = sum ;
        }
    }

    // ¦C¦L a ¯x°}
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < n ; ++j ) cout << a[i][j] <<  " " ;
        cout << endl ;
    }

    // ¦C¦L b ¯x°}
    cout << endl ;
    for ( i = 0 ; i < n ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) cout << b[i][j] <<  " " ;
        cout << endl ;
    }

    // ¦C¦L¯x°}­¼¿n c 
    cout << endl ;
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) cout << c[i][j] <<  " " ;
        cout << endl ;
    }

    return 0 ;
    
}

            
