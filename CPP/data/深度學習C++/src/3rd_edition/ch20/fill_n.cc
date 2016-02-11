#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std ;

int main() {

    const  int  S = 7 ;
    int         no[S] ;

    // 將 no 陣列填滿 1, 後列印 
    fill(no,no+S,1) ;
    copy(no,no+S,ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 使用 fill_n 填滿若干個數字
    int  i = 1 , size = S - 2 ;
    for ( ; size > 0 ; ++i , size -= 2 ) {
        fill_n(no+i,size,i+1) ;
        copy(no,no+S,ostream_iterator<int>(cout," ")) ;
        cout << endl ;
    }
    
    return 0 ;

}

            
