#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std ;

int main() {

    // 品茶連環詩 : 一
    string  tea_poem[5] = { "清" , "心" , "也" , "可" , "以" };
    string  new_poem[5] ;
    int     i ;
    
    for ( int i = 0 ; i < 5 ; ++i ) {
        rotate_copy( tea_poem , tea_poem+i , tea_poem+5 , new_poem ) ;
        copy( new_poem , new_poem+5 , ostream_iterator<string>(cout,"") ) ;
        cout << endl ;
    }
    cout << endl ;
    
    /******************************************************************

    // 品茶連環詩 : 二
    string  tea_poem2 = "清心也可以" ;
    
    for ( int i = 0 ; i < 5 ; ++i ) {
        cout << tea_poem2 << endl ;
        rotate( tea_poem2.begin() , tea_poem2.begin()+2 , tea_poem2.end() ) ;
    }        
    cout << endl ;

    // 品茶連環詩 : 三
    char  tea_poem3[] = "清心也可以" ;
    
    for ( int i = 0 ; i < 5 ; ++i ) {
        cout << tea_poem3 << endl ;
        rotate( tea_poem3 , tea_poem3+2 , tea__poem+10 ) ;
    }        
    cout << endl ;

    ******************************************************************/
    
    // 蘇小妹 : 連環詩 
    string  poem[14] = { "賞","花","歸","去","馬","如","飛",
                         "酒","力","微","醒","時","已","暮" };

    int     d[4] = { 0 , 3 , 4 , 3 };
    
    // 每次以 d[i] 的字數差距循環產生七言詩句
    for ( int i = 0 ; i < 4 ; ++i ) {
        rotate( poem , poem+d[i] , poem+14 ) ;
        copy( poem , poem+7 , ostream_iterator<string>(cout,"") ) ;
        cout << endl ;
    }

    return 0 ;
    
}

    
    
