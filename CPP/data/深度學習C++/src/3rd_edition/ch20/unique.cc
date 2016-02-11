#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std ;

// 浪琩ㄢ计琌计┪琌案计
bool  odd_even( int a , int b ) { return  a % 2 == b % 2 ; }

int main() {
    
    const int S = 10 ;
    int no[S] = { 23 , 55 , 55 , 98 , 12 , 34 , 34 , 34 , 73 , 43 };

    vector<int>            foo(no,no+S) ;
    vector<int>::iterator  iter ;

    cout << "> ﹍じ   : " ;
    copy( foo.begin() , foo.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 埃綟じ
    iter = unique( foo.begin() , foo.end() ) ;

    cout << "> 虫て(场)   : " ;
    copy( foo.begin() , iter , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    cout << "> 虫て(俱)   : " ;
    copy( foo.begin() , foo.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    vector<int>  bar ;
    copy( no , no+S , foo.begin() ) ;
    unique_copy( foo.begin() , foo.end() , back_inserter(bar) ) ;
    
    cout << "> 虫狡籹       : " ;
    copy( bar.begin() , bar.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 穝砞﹚ foo 
    copy( no , no+S , foo.begin() ) ;

    // 计案计虫て
    iter = unique( foo.begin() , foo.end() , odd_even ) ;
    
    cout << "> 案计虫て   : " ;
    copy( foo.begin() , iter , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 穝砞﹚ foo , bar 
    copy( no , no+S , foo.begin() ) ;
    bar.resize(0) ;
    
    // 计案计虫狡籹
    iter = unique_copy( foo.begin() , foo.end() , bar.begin() , odd_even ) ;
    
    cout << "> 案计虫狡籹 : " ;
    copy( bar.begin() , iter , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}
