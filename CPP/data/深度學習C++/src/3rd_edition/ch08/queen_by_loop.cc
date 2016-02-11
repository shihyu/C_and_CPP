#include <iostream>
#include <iomanip>

using namespace std ;

// 使用全域變數

// S : 棋盤大小 , queen : 皇后位置
const int  S = 8 ;
bool  queen[S][S] = { { false }, { false }, { false }, { false },
                      { false }, { false }, { false }, { false }
                    } ;

// 計算絕對值
int  abs( int x ) { return x > 0 ? x : -x ; }

// 檢查皇后在(r,c)位置是否為適當位置
bool  valid_position(int r , int c ) {
    int i , j , dx , dy ;
    for ( j = 0 ; j < c ; ++j ) 
        for ( i = 0 ; i < S ; ++i ) {
            if ( queen[i][j] ) {
                dx = abs(r-i) ;
                dy = c - j ;
                if ( dx == 0 || dy == 0 || dx == dy ) 
                    return false ;
            }
        }
    return true ;
}

// 列印所有皇后的位置
void  print_queen(int counter) {
    int i , j ;
    cout << "\n" << setw(7) << "[" << setw(3) << counter << "]\n" ;
    for ( i = 0 ; i < S ; ++i ) {
        for ( j = 0 ; j < S ; ++j ) 
            cout << setw(2) << ( queen[i][j] ? "Q" : "+" ) ;
        cout << endl ;
    }
}

// 主函式
int  main() {

    int  counter = 0 ;
    int  c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 ;
    int  r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 ;

    // 八層迴圈
    for ( c1 = 0 , r1 = 0 ; r1 < S ; ++r1 ) {

      if ( valid_position(r1,c1) ) {
        queen[r1][c1] = true ;

        for ( c2 = c1+1 , r2 = 0 ; r2 < S ; ++r2 ) {
          if ( valid_position(r2,c2) ) {
            queen[r2][c2] = true ;

            for ( c3 = c2+1 , r3 = 0 ; r3 < S ; ++r3 ) {
              if ( valid_position(r3,c3) ) {
                queen[r3][c3] = true ;

                for ( c4 = c3+1 , r4 = 0 ; r4 < S ; ++r4 ) {
                  if ( valid_position(r4,c4) ) {
                    queen[r4][c4] = true ;

                    for ( c5 = c4+1 , r5 = 0 ; r5 < S ; ++r5 ) {
                      if ( valid_position(r5,c5) ) {
                        queen[r5][c5] = true ;

                        for ( c6 = c5+1 , r6 = 0 ; r6 < S ; 
                              ++r6 ) {
                            if ( valid_position(r6,c6) ) {
                                queen[r6][c6] = true ;

                                for ( c7 = c6+1 , r7 = 0 ; r7 < S ; 
                                      ++r7 ) {
                                   if ( valid_position(r7,c7) ) {
                                     queen[r7][c7] = true ;

                                     for ( c8 = c7+1 , r8 = 0 ; 
                                           r8 < S ; ++r8 ) {
                                       if ( valid_position(r8,c8) ) {
                                           queen[r8][c8] = true ;
                                           print_queen(++counter) ;
                                           queen[r8][c8] = false ;
                                       }
                                     }
                                     queen[r7][c7] = false ;

                                   }
                                }
                                queen[r6][c6] = false ;

                            }
                        }
                        queen[r5][c5] = false ;
                        
                      }
                    }
                    queen[r4][c4] = false ;

                  }
                }
                queen[r3][c3] = false ;
                
              }
            }
            queen[r2][c2] = false ;
            
          }
        }
        queen[r1][c1] = false ;
            
      }
    }
	
    return 0 ;
    
}		 
