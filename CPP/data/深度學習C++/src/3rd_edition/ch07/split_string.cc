#include <iostream>
#include <string>

using namespace std ;

// 從英文句子中取出英文單字

int main() {
    
    int  i  ;
    
    string  Q = "Must you be so linear, Jean-Luc" ;
    
    int     count = 0 ;    // 字串數
    string  word      ;    // 儲存暫時使用的英文單字
    string  words[20] ;    // 字串陣列用來儲存英文單字
    
    for ( i = 0 ; i < Q.size() ; ++i ) {

        // 如果不是英文字母, 則提早進入下個迴圈
        if ( ! ( ( Q[i] >= 'a' && Q[i] <= 'z' ) ||
                 ( Q[i] >= 'A' && Q[i] <= 'Z' ) ) ) continue ;
        
        // 讓單字歸零
        word = "" ;

        // 重複將英文字母加上單字之後, 直到非英文字母為止
        do {
            word += Q[i] ;
            ++i ;
        } while (  ( Q[i] >= 'a' && Q[i] <= 'z' ) ||
                   ( Q[i] >= 'A' && Q[i] <= 'Z' ) ) ;

        words[count] = word ;
        
        // 單字數目進一
        ++count ;

    }
    
    // 列印所有英文單字
    for ( i = 0 ; i < count ; ++i ) {
        cout << i+1 << " : [" << words[i] << "]\n" ;
    }

    return 0 ;
    
}

