#include <iostream>
#include <algorithm>

using namespace std ;

struct  Equal {
    int  n ;
    Equal( int i ) : n(i) {}
    bool  operator() ( int a , int b ) { return  a%n == b%n ; }
};


int main() {
    
    int  no[8] = { 3 , 5 , 9 , 8 , 7 , 1 , 2 , 5 };
    int  *p = adjacent_find(no,no+8) ;
   
    if ( p == no+8 ) 
        cout << "> 沒有相鄰的元素是相同的" << endl ;
    else
        cout << "> 相同的相鄰元素 : " << *p << endl ;
    
    p = adjacent_find(no,no+8,Equal(4)) ;
    
    if ( p == no+8 ) 
        cout << "> 沒有被 4 後除後的餘數是相同且相鄰的元素" << endl ;
    else
        cout << "> 被 4 後除後的餘數是相同且相鄰的元素 : " 
             << *p << endl ;

    return 0 ;

}

    
