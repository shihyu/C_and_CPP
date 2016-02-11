#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;

int main() {
    
    int i , j , n ;
    int **s ;

    cout << "> 块よ皚计 (斗案计) : " ;
    cin >> n ;
    cout << endl ;
    
    s = new int*[n] ;
    for ( i = 0 ; i < n ; ++i ) s[i] = new int[n] ;

    srand( static_cast<unsigned int>(time(NULL)) ) ;
    
    // 纗 [0..9] 睹计
    for ( i = 0 ; i < n ; ++i ) 
        for ( j = 0 ; j < n ; ++j ) s[i][j] = rand()%10 ;

    //  S 痻皚
    cout << "> S : " << endl ;
    for ( i = 0 ; i < n ; ++i ) {
        for ( j = 0 ; j < n ; ++j ) cout << s[i][j] << " " ;
        cout << "\n" ;
    }
    cout << endl ;
    
    // よ皚︽计ㄓよ皚
    int m = n/2 ;

    // だ皌丁倒よ皚 
    int **a = new int*[m] ;
    int **b = new int*[m] ;
    int **c = new int*[m] ;
    int **d = new int*[m] ;
    
    for ( i = 0 ; i < m ; ++i ) {
        a[i] = new int[m] ;
        b[i] = new int[m] ;
        c[i] = new int[m] ;
        d[i] = new int[m] ;
    }
    

    // 砞﹚籔 A 痻皚
    cout << "> A : " << endl ;
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
            a[i][j] = s[i][j] ;
            cout << a[i][j] << " " ;
        }
        cout << "\n" ;
    }
    cout << endl ;

    // 砞﹚籔 B 痻皚
    cout << "> B : " << endl ;
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
            b[i][j] = s[i][j+m] ;
            cout << b[i][j] << " " ;
        }
        cout << "\n" ;
    }
    cout << endl ;

    // 砞﹚籔 C 痻皚
    cout << "> C : " << endl ;
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
            c[i][j] = s[i+m][j] ;
            cout << c[i][j] << " " ;
        }
        cout << "\n" ;
    }
    cout << endl ;

    // 砞﹚籔 D 痻皚
    cout << "> D : " << endl ;
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
            d[i][j] = s[i+m][j+m] ;
            cout << d[i][j] << " " ;
        }
        cout << "\n" ;
    }
    cout << endl ;

    for ( i = 0 ; i < n ; ++i ) delete [] s[i] ;
    delete [] s ;
    
    for ( i = 0 ; i < m ; ++i ) {
        delete [] a[i] ;  delete [] b[i] ;
        delete [] c[i] ;  delete [] d[i] ;
    }
    
    delete [] a ;
    delete [] b ;
    delete [] c ;
    delete [] d ;

    return 0 ;
    
}
