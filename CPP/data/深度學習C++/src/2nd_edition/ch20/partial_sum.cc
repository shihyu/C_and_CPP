#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std ;

// ㄧΑ度 b 箂猭笲衡
int positive_sum ( int a , int b ) { return ( b > 0 ? a + b : a ) ; }


int main() {
    
    const  int   S = 5 ;
    int          no[S] = { 2 , 4 , -3 , 1 , 4 };
    vector<int>  s(S) ;
    
    //  no 皚
    cout << "> 俱计皚   : " ;
    copy( no , no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 盢场㎝挡狦秖皚 s 
    partial_sum( no , no+S , s.begin() ) ;
    cout << "> 皚场㎝ : " ;
    copy( s.begin() , s.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // タ俱计
    partial_sum( no , no+S , s.begin() , positive_sum ) ;
    cout << "> タ计场㎝ : " ;
    copy( s.begin() , s.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 璸衡縩
    partial_sum( no , no+S , s.begin() , multiplies<int>() ) ;
    cout << "> 场縩 : " ;
    copy( s.begin() , s.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

