#include <iostream>
#include <algorithm>
#include <vector>

using namespace std ;

int main() {

    int          no[3] = { 10 , 20 , 30 };

    vector<int>  foo(2)  ;
    foo[0] = 40 ;  foo[1] = 50 ;
    
    vector<int>::iterator  iter = foo.begin() ;

    cout << "對調前 : " << endl 
         << "> no  = " << no[0] << " " << no[1] << " " << no[2] << endl 
         << "> foo = " << foo[0] << " " << foo[1] << endl ;

    // 對調 no[1] 與 *iter 兩資料值
    iter_swap( no+1 , iter ) ;
    
    // 對調 no[2] 與 foo[1] 
    swap( no[2] , foo[1] ) ;
    
    cout << "對調後 : " << endl 
         << "> no  = " << no[0] << " " << no[1] << " " << no[2] << endl
         << "> foo = " << foo[0] << " " << foo[1] << endl ;

    return 0 ;

}

    
