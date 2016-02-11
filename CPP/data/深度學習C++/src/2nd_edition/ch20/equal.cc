#include <iostream>
#include <algorithm>
#include <vector>

using namespace std ;

// 浪琩琌常案计
struct  even {
    bool operator() ( int a , int b ) const { 
        return ( a % 2 == 0 && b % 2 == 0 ) ? true : false ; 
    }
};


int main() {
    
    int          foo[5] = { 2 , 2 , 4 , 6 , 8 };
    vector<int>  bar(5,2) ;   // 5  2 

    // ㄏノゅ true 籔 false ㄓ痷安块
    cout << boolalpha ;

    cout << equal(foo,foo+5,bar.begin()) << endl ;
    cout << equal(foo,foo+5,bar.begin(),even()) << endl ;

    return 0 ;
    
}

            
