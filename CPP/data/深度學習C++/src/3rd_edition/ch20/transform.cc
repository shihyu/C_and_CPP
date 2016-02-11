#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>

using namespace std ;

// 計算字串字元數 
int  char_count( const string& s ) { 
    return s.size() ; 
}

// 將每個字母在字母表的順序旋轉字串長度個位置
string  rotate_char( string s , int no ) {

        for ( int i = 0 ; i < s.size() ; ++i ) 
            
            if ( 'a' <= s[i] && s[i] <= 'z' ) {
                s[i] +=  s.size() ;
                if ( s[i] > 'z' ) s[i] -= 26 ;
            } else if ( 'A' <= s[i] && s[i] <= 'Z' ) {
                s[i] +=  s.size() ;
                if ( s[i] > 'Z' ) s[i] -= 26 ;
            }
    
    return s ;
}

int main() {
    
    const  int  S = 11 ;
    string  Q[S] = { "I" , "believed" ,  "that" , "my" ,  
                      "exact" , "words" , "were" , "dangerous" , 
                      "savage" , "child" , "race" } ;

    vector<int>     chars(S) ;
    vector<string>  code ;

    int  i  ;
    for ( i = 0 ; i < S ; ++i ) cout << Q[i] << " " ;
    cout << endl ;

    // 計算每個單字中母音的個數後將結果存於向量陣列中
    transform( Q , Q+S , chars.begin() , char_count ) ;

    for ( i = 0 ; i < S ; ++i ) 
        cout << left << setw(Q[i].size()) << chars[i] << " " ;
    cout << endl ;

    // 將 Q 內的字串字母依單字長度旋轉字母, 轉換後的資料
    // 由末端插入 code 字串陣列中
    transform( Q , Q+S , chars.begin() , 
               back_inserter(code) , rotate_char ) ;

    for ( i = 0 ; i < S ; ++i ) cout << code[i] << " " ;
    cout << endl ;

    return 0 ;
    
}

        
            
