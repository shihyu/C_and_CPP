#include <iostream>
#include <numeric>
#include <iterator>

using namespace std ;

int main() {

    const int S = 5 ;
    int no[S] = { 3 , 2 , 4 , 1 , 2 };

    cout << "> ¼Æ¦C : " ;
    copy( no , no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    int sum = 0 ;
    cout << "> Á`©M = " 
         << accumulate( no , no+S , sum )  ;
    
    int product = 1 ;
    cout << "  ,  ­¼¿n = "
         << accumulate( no , no+S , product , multiplies<int>() ) 
         << endl ;

    return 0 ;
    
}
