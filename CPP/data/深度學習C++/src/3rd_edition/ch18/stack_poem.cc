#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std ;

int main() {

    char  p[] =  "斜風繞徑曲  從石帶山連  花餘拂戲鳥  數密隱鳴蟬" ;

    // 計算字串陣列的長度
    int    size = sizeof(p) / sizeof(char) ;

    // c++ 字串堆疊
    stack< string , vector<string> >  poem ;

    // 每兩個字母當成一個字串送入堆疊
    for ( int i = 0 ; i < size ; i+=2 ) 
        poem.push( string(p+i,p+i+2) ) ;
    
    // 將堆疊元素一一印出後移除
    while ( ! poem.empty() ) {
        cout << poem.top() ;
        poem.pop() ;
    }
    cout << endl ;
    return 0 ;

}
