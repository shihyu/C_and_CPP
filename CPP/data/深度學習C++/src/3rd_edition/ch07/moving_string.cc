#include <iostream>
#include <string>
#include <unistd.h>   

// 如果是使用 visual C++ 編譯器  則使用以下標頭檔
// #include <cstdlib>    

using namespace std ;

int main() {

    // 跑馬燈上的文字
    string  foo = "滾滾長江東逝水，浪花淘盡英雄。"
                  "是非成敗轉頭空：青山依舊在，幾度夕陽紅。" ;
    
    int  i ;

    // 列印的起始位置
    int  p = 0 ;
    
    while ( 1 ) {
    
        // 由 p 位置起循環列印整行
        for ( i = 0  ; i < foo.size() ; i+=2 ) {
            cout << foo[(p+i)%foo.size()] << foo[(p+i+1)%foo.size()] 
                 << flush ;
        }

        // 程式休息一秒
        sleep(1) ;          

        // _sleep(1000) ;  // 如果使用 visual C++, 則須用此敘述

        // 將鍵盤游標重到行首
        cout << "\r" ;
    
        p+=2 ;
        
    }

    return 0 ;
    
}
