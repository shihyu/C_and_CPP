#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std ;

int main() {
  
    setlocale( LC_ALL , "zh_TW.UTF-8") ;

    // 設定讀入的中文文字高度與寬度
    const int MAX_H = 24 ;
    const int MAX_W = 80 ;

    wstring          line ;
    wifstream        poem("utf8_poem.db") ;

    // 定義字串資料串流物件陣列
    wostringstream   poemstring[MAX_W]  ;

    locale  utf8("zh_TW.UTF-8");     

    // 設定檔案資料串流處理 UTF-8 中文字串
    poem.imbue(utf8) ;  

    // 記錄在讀入的所有行數中最多字元的個數
    int no = 0 , max = 0 ;
    int i , j ;

    // 讀入橫行中文, 並一一存入字串資料流物件陣列
    while ( getline( poem , line ) ) {
        if ( max < line.length() ) max = line.length() ;
        poemstring[no++] << line ;
    }

    // 末尾補上若干個中文空白字元，使每個 poemstring 有等長的寬字串
    for ( i = 0 ; i < no ; ++i ) {
        j = poemstring[i].str().size() ;
        if ( j < max ) poemstring[i] << wstring(max-j,L'　' ) ;
    }

    // 列印
    for ( j = 0 ; j < max ; ++j ) {
        for ( i = no-1 ; i >= 0 ; --i ) {
            wcout << poemstring[i].str()[j] << L'　' ;
        }
        wcout << endl ;
    }

    return 0 ;
    
}






