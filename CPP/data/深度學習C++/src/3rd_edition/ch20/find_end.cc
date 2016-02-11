#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std ;

// 大小寫無關
bool  case_insensitive ( char a , char b ) {
    if ( 'a' <= a && a <= 'z' ) a = a - 'a' + 'A' ;
    if ( 'a' <= b && b <= 'z' ) b = b - 'a' + 'A' ;
    return  a == b ;
}

int main() {
    
    string  pwd = "ratoxtigerrabbitdragonoxoxrat" ;
    string  code ;
    string::iterator  iter , iter2 ;
    
    int  n ;
    cout << pwd << endl ;

    // 重複找尋  按 ctrl-c 離開
    while ( 1 ) {
        
        // 輸入欲找尋字串
        cin >> code ;

        iter = pwd.end() ;
        n = 0 ;
        
        while( 1 )  {

            // 在 [pwd.begin(),iter) 內找尋最後一筆字串 code
            iter2 = find_end( pwd.begin() , iter , 
                              code.begin() , code.end() ,
                              case_insensitive ) ;

            // 沒找到則跳離
            if ( iter2 == iter ) break ;

            // 找到, 則計數加一, 重定搜尋末尾
            ++n ; iter = iter2 ;
        }
        cout << "> count : " << n << endl ;
    }

    return 0 ;
    
}
