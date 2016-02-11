#include <iostream>
#include <iomanip>

using namespace std ;

int  main() {
    
    int  i , j , n ;
    
    cout << "> 輸入向量長度 : " ;
    cin >> n ;

    int  *a , *b , **M ;
    
    a = new int[n] ;
    b = new int[n] ;

    M = new int*[n] ;
    for ( i = 0 ; i < n ; ++i )  M[i] = new int[n] ;
    
    cout << "> 輸入第一個向量所有的元素 : " ;
    for ( i = 0 ; i < n ; ++i ) cin >> *(a+i) ;
    
    cout << "> 輸入第二個向量所有的元素 : " ;
    for ( i = 0 ; i < n ; ++i ) cin >> *(b+i) ;

    // 計算矩陣 M[i][j] = a[i] * b[j]
    for ( i = 0 ; i < n ; ++i ) {
        for ( j = 0 ; j < n ; ++j ) M[i][j] = *(a+i) * *(b+j) ;
    }
    
    // 列印 a b = M 
    for ( i = 0 ; i < n ; ++i ) {

        cout << setw(2) << *(a+i) ;

        if ( i == static_cast<int>(n/2) ) {
            cout << "  * " ;
            for ( j = 0 ; j < n ; ++j ) cout << setw(2) << *(b+j) ;
            cout << "  = " ;
        } else {
            cout << setw(8+2*n) << " " ;
        }
        for ( j = 0 ; j < n ; ++j ) 
            cout << setw(3) << M[i][j] << " " ;
        
        cout << endl ;
    }

    // 將 a , b , M 的記憶空間送回系統
    delete [] a ;   delete [] b ;   

    for ( i = 0 ; i < n ; ++i ) delete [] M[i] ;
    delete [] M ;
    

    return 0 ;
    
}


