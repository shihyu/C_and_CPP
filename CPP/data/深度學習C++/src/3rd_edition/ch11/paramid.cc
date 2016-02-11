#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int   j , n ;
    
    char  a[] = " " ;
    char  b[100] ;

    // 讀取一行字串
    cout << "> enter string : " ;

    cin.unsetf(ios::skipws) ;

    int  i = 0 ;
    do {
        cin >> b[i] ;
    } while ( b[i++] != '\n' ) ;
    
    b[i-1] = '\0' ;

    cin.setf(ios::skipws) ;

    // 設定高度
    cout << "> input n : " ;
    cin >> n ;

    for ( j = 0 ; j < n ; ++j ) {

        cout << "\n" << setfill(' ') << setw(n-j) << " " ;

        for ( i = 0 ; b[i] != '\0' ; ++i ) {
            
            a[0] = b[i] ;
            cout << setfill(b[i]) 
                 << ( i % 2 == 0 ? setw(2*j+1) : setw(2*(n-j)-1) )
                 << a << ' ' ;
            
        }
        
    }

    cout << endl ;
    return 0 ;
    
}
