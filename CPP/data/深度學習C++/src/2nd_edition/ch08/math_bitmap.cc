#include <iostream>
#include <string>

using namespace std ;

// 每個數字為 5 x 5 的點矩陣
const int ROW = 5 , COL = 5 ;

// 建構點矩陣
void  build_bitmap( const string& , string * ) ;

// 列印點矩陣
void  print_bitmap( const string * ) ;

// 清除點矩陣
void  clear_bitmap( string * ) ;
    

int main() {
    
    // no     : 為輸入的數字字串 
    // bitmap : 陣列為每一列所構成的點矩陣字元資料
    string  no , bitmap[ROW] ;

    while( 1 ) {
        cout << "> 輸入正整數字串 : " ;
        cin >> no ;
        if ( no == "0" ) break ;           // 跳離
        build_bitmap( no , bitmap ) ;      // 建構點矩陣資料
        print_bitmap( bitmap ) ;           // 列印數字的點矩陣
        clear_bitmap( bitmap ) ;           // 清除點矩陣
        cout << endl ;
    }

}
              
// 建構輸入數字字串的點矩陣
void  build_bitmap( const string& no , string bitmap[] ) {

    // 點矩陣數字 : 共十個數字 0 , 1 , 2 , ... , 9
    static unsigned char no_bitmap[10][ROW] = 
        { {14,17,17,17,14} , {4,12,4,4,14} , {14,17,2,4,31}   ,
          {30,1,14,1,30}   , {2,6,10,31,2} , {31,16,30,1,30}  ,
          {15,16,30,17,14} , {31,1,2,4,8}  , {14,17,14,17,14} ,
          {14,17,15,1,30}   };

    int i , n , r , c ;
    for ( r = 0 ; r < ROW ; ++r ) {
        for ( i = 0 ; i < no.size() ; ++i ) {

            // 計算每一列所對應的點矩陣資料
            n = no_bitmap[ no[i] - '0' ][r] ;

            // 列的點矩陣數字內若有數字  則以星號代替, 否則加上空白
            for ( c = COL-1 ; c >= 0 ; --c ) {
                bitmap[r] += ( n & ( 1 << c ) ? '*' : ' ' ) ;
            }
            
            // 每個數字之間用兩個空白隔開
            bitmap[r] += "  " ;
        }
    }
}

// 列印點矩陣
void  print_bitmap( const string * bitmap ) {
    for ( int i = 0 ; i < ROW ; ++i ) cout << bitmap[i] << endl ;
}

// 清除點矩陣
void  clear_bitmap( string bitmap[] ) {
    for ( int i = 0 ; i < ROW ; ++i ) bitmap[i] = "" ;
}
              
              
              
              
              
                
            
    
