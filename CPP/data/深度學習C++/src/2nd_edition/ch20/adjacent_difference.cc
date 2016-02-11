#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>

using namespace std ;

// 璝畉禯箂, 玥砞箂. 
// 叫痙種 : b 把计┮じ a 把计┮じ
int  positive_difference( int b , int a ) {
    int  d = b - a ;
    return  ( d < 0 ? 0 : d ) ;
}

int main() {
    
    int x[5] = { 4 , 2 , 2 , 5 , 2 };
    int dx[5] ;
    
    cout << "> 皚   = " ;
    copy( x , x+5 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    adjacent_difference( x , x+5 , dx ) ;
    
    cout << "> 畉禯   = " ;
    copy( dx , dx+5 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    adjacent_difference( x , x+5 , dx , positive_difference ) ;
    
    cout << "> タ畉禯 = " ;
    copy( dx , dx+5 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

