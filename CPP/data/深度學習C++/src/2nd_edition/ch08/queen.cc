#include <iostream>
#include <iomanip>

using namespace std ;

// 使用全域變數

// S : 棋盤大小 , queen : 皇后位置
const int  S = 8 ;
bool  queen[S][S] = { { false }, { false }, { false }, { false },
                      { false }, { false }, { false }, { false } };

// 計算絕對值
int  abs( int x ) { return x > 0 ? x : -x ; }

// 檢查新的皇后若擺放在 (r,c) 位置是否適當
bool  valid_position(int r , int c ) {

    int i , j , dx , dy ;

    // 檢查是否與已有的皇后在同一行, 同一列或在對角線上
    for ( j = 0 ; j < c ; ++j ) 
        for ( i = 0 ; i < S ; ++i ) {
            if ( queen[i][j] ) {
                dx = abs(r-i) ;
                dy = c - j ;
                if ( dx == 0 || dy == 0 || dx == dy ) return false ;
            }
        }
    return true ;

}

// 列印所有的皇后位置
void  print_queen(int counter) {
    int i , j ;
    cout << "\n" << setw(7) << "[" << setw(3) << counter << "]\n" ;
    for ( i = 0 ; i < S ; ++i ) {
        for ( j = 0 ; j < S ; ++j ) 
            cout << setw(2) << ( queen[i][j] ? "Q" : "+" ) ;
        cout << endl ;
    }
}


// 遞迴找尋皇后位置
void  locate_queen( int col ) {

    int  row ;
    static int  counter = 0 ;

    if ( col == S ) {

        print_queen(++counter) ;

    } else {

        for ( row = 0 ; row < S ; ++row ) {
            if ( valid_position(row,col) ) {
                queen[row][col] = true ;
                locate_queen(col+1) ;
                queen[row][col] = false ;
            }
        }

    }
}

// 主函式
int  main() {

    int  col = 0 ;

    locate_queen(col) ;

    return 0 ;
    
}		 
