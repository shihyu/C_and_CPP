#include  <iostream>
#include  <string>
#include  <sstream>
#include  <iomanip>

using namespace std ;

int main() {
    
    string         line ;
    istringstream  math_string ;
    
    int      no , sum ;
    char     op ;
    
    // 重複執行, 直到輸入空白行為止
    while ( 1 ) {

        cout << "> " ;
        
        // 讀入一行資料後存入字串資料串流物件中
        getline( cin , line ) ;
        if ( line == "" ) break ;
        
        math_string.str( line ) ;

        // 讀入第一個數字
        math_string >> sum ;

        // 由字串資料串流物件讀入一個運算字元與數字
        while ( math_string >> op >> no ) {

            cout << setw(3) << sum << ' ' ;
            ( op == '+' ) ? ( sum += no ) : ( sum -= no ) ;

            cout << op << ' ' << setw(3) << no << " = " 
                 << setw(3) << sum << endl ;
            
        }

        cout << endl ;

        // 清除之前的輸入錯誤旗幟, 以利往後資料的讀取
        math_string.clear() ;

    }

    return 0 ;
    
}
