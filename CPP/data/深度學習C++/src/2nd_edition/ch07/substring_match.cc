#include <iostream>

using namespace std ;

int main() {
    
    // 比對字串
    char  str[] = "AGACCGGTATTACGGTTACCTCCACTCGTTACCCTGTCCCATTTAG" ;
    char  substr[100] ;
    
    bool  found ;
    int   count = 0; 
    int   i , j ;
    int   len , len1 , len2 ;
    
    cout << "> 輸入字串 : " ;
    cin >> substr ;

    // 所要比對的字串長度, 不包含空字元
    len1 = 0 ;
    while( str[len1] != '\0' ) ++len1 ;

    // 所要找尋的字串長度, 不包含空字元
    len2 = 0 ;
    while( substr[len2] != '\0' ) ++len2 ;

    // 列印比對字串
    cout << str << endl ;

    // 計算最多迴圈循環次數
    len = len1 - len2 + 1 ;

    // 迴圈開始
    for ( i = 0 ; i < len ; ++i ) {

        // 比對字串
        found = true ;
        for ( j = 0 ; j < len2 ; ++j ) {
            if ( str[i+j] != substr[j] ) {
                found = false ;
                break ;
            }
        }

        // 計算找到的次數        
        if ( found ) ++count ;

        // 列印找到的起始位置
        cout << ( found ? "^" : " " ) ;
        
    }

    cout << "\n> 找到次數 : " << count << endl ;

    return 0 ;
    
}
