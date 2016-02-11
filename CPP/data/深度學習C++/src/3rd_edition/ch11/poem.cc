#include  <iostream>
#include  <fstream>
#include  <sstream>
#include  <string>
#include  <iomanip>

using namespace std ;

int main( int argc , char *argv[]) {

    // 如果忘了在命令行後加入欲處理的中文檔案名稱, 則程式結束
    if ( argc == 1 ) return 1 ;

    // 設定讀入的中文文字高度與寬度
    const int MAX_H = 24*2 ;
    const int MAX_W = 80   ;

    string          line ;
    ifstream        poem( argv[1] ) ;

    // 定義字串資料流物件陣列
    ostringstream   poemstring[MAX_W]  ;

    // 記錄在讀入的所有行數中最多字元的個數
    int  no = 0 , max = 0 ;

    // 讀入橫行中文, 並一一存入字串資料流物件陣列
    while ( getline( poem , line ) ) {
        
        if ( max < line.length() ) max = line.length() ;
        poemstring[no++] << setw(MAX_H) << setiosflags(ios::left) 
                         << line.c_str() ;
        
    }

    // 兩個兩個字元輸出, 並在每一行之間另外加入一空白行
    int i , j ;
    for ( j = 0 ; j < max ; j += 2 ) {
        for ( i = no-1 ; i >= 0 ; --i ) {
            cout << poemstring[i].str()[j] << poemstring[i].str()[j+1]
                 << "  " ;
        }
        cout << endl ;
    }

    return 0 ;
    
}

