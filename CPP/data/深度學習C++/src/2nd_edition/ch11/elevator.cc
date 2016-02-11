#include  <iostream>
#include  <sstream>
#include  <iomanip>
#include  <string>

// 樓層層數
const int MAX_FLOOR = 10 ;          

// 昇降梯昇降方向
enum  DIRECTION  { up   , down } ;  

// 昇降梯在某樓層是否跳過不停或者停止
enum  STATUS     { skip , stop } ;  

using  namespace  std ;

int  main() {
    
    int        i  , no ;

    // 設定內定的昇降梯現在所在的樓層, 昇降方向, 欲停止的樓層
    int        current_floor       = 1         ;
    DIRECTION  direction           = up        ;
    STATUS     floor[MAX_FLOOR+1]  = { skip }  ;
    
    string         line           ;
    istringstream  stops( line )  ;
    
    // 昇降梯為連續運轉, 使用 Ctrl-c 跳離程式
    while ( 1 ) {
        
        cout << "[" << setw(2) << current_floor << "] : " ;

        // 讀入昇降梯停止樓層
        getline( cin , line ) ;
        stops.str( line ) ;

        // 設定昇降梯停止樓層
        while ( stops >> no ) {
            if ( ( no >= 1 ) && ( no <= MAX_FLOOR ) ) 
                floor[no] = stop ;
        }
        
        floor[current_floor] = skip ;

        // 根據輸入的樓層資料, 決定昇降梯接下來的昇降方向
        if ( direction == up || current_floor == MAX_FLOOR ) {

            direction = down ;
            for ( i = current_floor+1 ; i <= MAX_FLOOR ; ++i ) 
                if ( floor[i] == stop ) direction = up ;

        } else {

            direction = up ;
            for ( i = 1 ; i < current_floor ; ++i ) 
                if ( floor[i] == stop ) direction = down ;

        }

        // 根據昇降方向, 找出昇降梯下一個須要停止的樓層
        if ( direction == up ) {

            for ( i = current_floor+1 ; i <= MAX_FLOOR ; ++i ) {
                if ( floor[i] == stop ) {
                    current_floor = i ;
                    break ;
                }
            }
            
        } else {
            
            for ( i = current_floor-1 ; i >= 1 ; --i ) {
                if ( floor[i] == stop ) {
                    current_floor = i ;
                    break ;
                }
            }

        }

        stops.clear() ;    // 清除錯誤旗幟
        
    }

    return 0 ;
    
}
