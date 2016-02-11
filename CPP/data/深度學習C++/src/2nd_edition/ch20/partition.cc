#include <iostream>
#include <algorithm>
#include <string>

using namespace std ;

// 檢查字元是否為母音
bool  vowel ( char c ) {
    return  ( c == 'a' || c == 'e' || c == 'i' || 
              c == 'o' || c == 'u' ) ? true : false ;
}

int main() {

    string  Picard  = "sleep, Data. sleep" ;

    cout << "原有字串         > " << Picard << endl ;

    // 將母音提取到字串的前面
    partition( Picard.begin() , Picard.end() , vowel ) ;

    cout << "partition        > " << Picard << endl ;

    // 重新設定
    Picard = "sleep, Data. sleep" ;

    // 將母音提取到字串的前面, 但母音的原有前後次序保持不變
    stable_partition( Picard.begin() , Picard.end() , vowel ) ;

    cout << "stable partition > " << Picard << endl ;

    return 0 ;
    
}
