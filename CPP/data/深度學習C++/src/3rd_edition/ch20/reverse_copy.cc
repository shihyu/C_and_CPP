#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std ;

int main() {
    
    char   p[] =  "斜風繞徑曲  從石帶山連  花餘拂戲鳥  數密隱鳴蟬" ;

    // 計算 p 字串的文字長度
    int  size = sizeof(p)/sizeof(char)-1 ;

    vector<string>  poem , new_poem ;

    // 以每兩個字母當成一個字串讀入
    for ( int i = 0 ; i < size ; i+=2 ) 
        poem.push_back( string(p+i,p+i+2) ) ;

    // 列印詩句
    copy(poem.begin(),poem.end(),ostream_iterator<string>(cout,"") ) ;
    cout << endl ;

    // 產生迴文詩
    reverse_copy( poem.begin() , poem.end() , back_inserter(new_poem) ) ;

    // 列印迴文詩句
    copy(new_poem.begin(),new_poem.end(),ostream_iterator<string>(cout,"") ) ;
    cout << endl ;
    
    return 0 ;
    
}

    
