#include <iostream>
#include <algorithm>
#include <string>

using namespace std ;

// 判斷字元是否為大寫字元
struct  upper_case {
    bool  operator() ( char c ) const {
        return ( c >= 'A' && c <= 'Z' ) ? true : false ;
    }
};


int main() {
    
    string   Q = "Must you be so linear, Jean-Luc" ;

    // 計算 o 字母的個數
    cout << count( Q.begin() , Q.end() , 'o' ) << endl ;

    // 計算大寫字母的個數
    cout << count_if( Q.begin() , Q.end() , upper_case() ) << endl ;

    return 0 ;
    
}

            
