#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std ;

// 字元比較函式物件, 不分大小寫
struct case_insensitive {
    bool  operator() ( char a , char b ) const {
        if ( a >= 'a' ) a = a - 'a' + 'A' ;
        if ( b >= 'a' ) b = b - 'a' + 'A' ;
        return  a < b ;
    }
};

int main() {

    // 一個已排序的字母陣列
    const int S = 10 ;
    char  str[S] = { 'a' , 'c' , 'e' , 'e' , 'm' , 
                     'm' , 'm' , 'u' , 'u' , 'v' } ;
    
    // 列印字母陣列
    copy(str,str+S,ostream_iterator<char>(cout," ")) ;
    cout << endl ;

    char  *lower , *upper ;

    // 'a' 到 'z' 每四個字母比較一次
    for ( char c = 'a' ; c <= 'z' ; c += 4 ) {

        lower = lower_bound( str , str+S , c ) ;
        upper = upper_bound( str , str+S , c ) ;
        
        cout << c << " : [ " 
             << ( lower != str+S ? *lower : '-' ) << " , " 
             << ( upper != str+S ? *upper : '-' ) << " )" << endl ;

    }
    cout << endl ;
    
    // 定義一成對物件, 內含兩個字元指標
    pair<char*,char*>  range ;

    // 若是大寫字母, 則使用比較函式忽略字母大小寫
    for ( char c = 'A' ; c <= 'Z' ; c += 4 ) {

        range = equal_range( str , str+S , c , case_insensitive() ) ;
        cout << c << " : [ " 
             << ( range.first  != str+S ? *(range.first) : '*' ) 
             << " , " 
             << ( range.second != str+S ? *(range.second) : '*' )
             << " )" << endl ;

    }

    return 0 ;
    
}

    
