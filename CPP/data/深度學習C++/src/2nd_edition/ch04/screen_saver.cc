#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std ;

const char*  esc    = "\x1b[" ;
const char*  sep    = ";" ;
const char*  clr    = "\x1b[2J" ;

int main() {
    
    // 螢幕的列數與行數
    const int ROW    = 24 ;
    const int COL    = 80 ;

    int  i , row , col , color ;

    // 設定亂數
    srand( static_cast<unsigned>(time(NULL)) ) ;

    // 清除畫面
    cout << clr << flush ;

    // 無窮迴圈, 請以岔斷鍵 (ctrl-C) 離開
    while ( 1 ) {

        // 用亂數決定 row 與 col 的位置
        row   = rand() % ROW + 1 ;  
        col   = rand() % COL + 1 ;  
        color = rand() % 8 ;
        
        // 在 ( row , col ) 方塊座標處印出彩色方塊
        cout << esc << row << sep << col  << "H"
             << esc << 4 << color << "m" << " " << flush ;

        // 空轉一段時間 : 50000000 次加法時間
        for ( i = 0 ; i < 50000000 ; ++i ) ;

    }

    return 0 ;
    
}
