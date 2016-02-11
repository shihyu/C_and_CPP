#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int  i , j , no ;
    
    int  pascal[20][20] ;
    
    cout << "> 輸入巴斯卡三角形的高度 : " ;
    cin >> no ;
        
    for ( i = 0 ; i < no ; ++i ) {

        cout << setw(3*(no-i)) << " " ;

        for ( j = 0 ; j <= i ; ++j ) {

            if ( j == 0 || i == j )
                pascal[i][j] = 1 ;
            else 
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j] ;

            cout << setw(6) << pascal[i][j] ;
        }

        cout << endl ;

    }

    return 0 ;
    
}
