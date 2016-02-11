#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std ;

int main() {

    // 一個已排序完成的整數陣列
    const int S = 10 ;
    char  str[S] = { 'a' , 'c' , 'e' , 'e' , 'm' , 
                     'm' , 'm' , 'u' , 'u' , 'v' } ;
    
    // 列印此陣列
    copy(str,str+S,ostream_iterator<char>(cout," ")) ;
    cout << endl ;
    
    char  *lower , *upper ;
    
    for ( char i = 'a' ; i <= 'z' ; i += 4 ) {

        cout << i << " : [ " ;
        lower = lower_bound( str , str+S , i ) ;
        upper = upper_bound( str , str+S , i ) ;
        
        cout << ( lower != str+S ? *lower : '-' ) ;
        cout << " , " ;

        cout << ( upper != str+S ? *upper : '-' );
        
        cout << " ]" << endl ;
        
    }
    
}

    
