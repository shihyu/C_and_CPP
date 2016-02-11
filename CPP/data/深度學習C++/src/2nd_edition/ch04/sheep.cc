#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;

int main() {
    
    int  right_choice = 0 , total_no = 1000000 ;
    int  i , j , car_door , guest_door , sheep_door , last_door ;

    // 用時間設定亂數函數的初值
    srand( static_cast<unsigned int>( time(NULL) ) ) ;

    // 測試 1000000 次
    for ( i = 0 ; i < total_no ; ++i ) {
        
        // 用亂數設定車子的位置 : 1 到 3 之間
        car_door = rand() % 3 + 1 ;
        
        // 來賓所選擇門的位置
        guest_door = rand() % 3 + 1 ;
        
        // 主持人找出不是來賓所選擇門的其它兩扇門中有羊的門
        for ( j = 1 ; j <= 3 ; ++j ) {
            if ( j != guest_door && j != car_door ) {
                sheep_door = j ;
                break ;
            }
        }
        
        // 找出最後一扇門, 也就是可以更換的門
        for ( j = 1 ; j <= 3 ; ++j ) {
            if ( j != guest_door && j != sheep_door ) {
                last_door = j ;
                break ;
            }
        }
        
        // 檢查更換的門後是否有汽車, 如果是則記錄下來
        if ( last_door == car_door ) {
            right_choice += 1 ;
        }

    }

    // 印出更換後猜對的機率
    cout << ( right_choice * 1.0 / total_no ) << endl ;

    return 0 ;
    
}
