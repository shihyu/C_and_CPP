#include  <iostream>
#include  <fstream>
#include  <string>

using namespace std ;

int main() {

    // 轉碼後的每一橫行字元數最多為 45 個字元
    const int     max_char_per_line = 45 ;

    // 轉碼文字的起始字元
    char          starting_char     = ' ' ;

    int           i , no , total_char  ;
    unsigned int  a , num[4] ;
    string        infile , line ;

    cout << "> 輸入二位元檔名 : " ;
    cin  >> infile ;
    cout << "\n> encoded  output :" << endl ;

    // 開啟二位元資料檔    
    ifstream  in( infile.c_str() , ios::in | ios::binary ) ;

    // num 為預定位元陣列用於作位元運算
    // num[3] = 111111              
    // num[2] = 111111000000
    // num[1] = 111111000000000000  
    // num[0] = 111111000000000000000000

    num[3] = 63                 ;   num[2] = ( num[3] << 6 ) ;
    num[1] = ( num[3] << 12 )   ;   num[0] = ( num[3] << 18 ) ;

    while ( 1 ) {
        
        line = "" ;
        total_char = 0 ;
        
        do {

            // 讀取 3 位元組資料到一整數 a
            a = 0 ;
            in.read( reinterpret_cast<char*>(&a) , 3 ) ;

            // 如果使用 MOTOROLA 的中央處理器 :  
            // 由於只讀了三個位元組的資料, 且讀入的資料被放在
            // 整數左邊三個位元組的位置, 因此須讓整數資料向往
            // 右移八個位元位置
            // a >>= 8  ;

            // 如果使用英代爾 (INTEL) 的中央處理器 :
            // 則須將上一行程式碼以下行程式碼取代, 
            // 目的在將讀入的第 1 個與第 3 個位元組資料對調
            a = ( ( ( a & 255 ) << 16 ) | ( a & (255<<8) ) | 
                  ( a >> 16 ) ) ;
            
            if ( in.gcount() == 0 ) 

                break ;         // 如果沒讀到任何資料, 則離開

            else {

                // 計算讀入的字元數相當於多少六個位元為切割單位
                no = in.gcount() + 1 ;
                
                // 以六位元為一單位, 開始轉碼
                for ( i = 0 ; i < no ; ++i ) 
                    line  += ( ( a & num[i] ) >> ((3-i)*6) ) + 
                             starting_char ;

                // 計算所讀入的字元數
                total_char += in.gcount() ;
        
            }
            
        } while ( total_char < max_char_per_line ) ;

        // 列印總字元數及轉碼後字串
        cout << static_cast<char>(total_char+starting_char) 
             << line.c_str() << endl ;

        // 檔案末尾
        if ( in.gcount() == 0 ) break ;
            
    }

    in.close() ;

    return 0 ;

}
