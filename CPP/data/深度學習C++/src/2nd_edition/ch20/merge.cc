#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std ;

// 比較兩整數的個位數大小
bool  cmp_last_digit( int a , int b ) { return a%10 < b%10 ; }

int main() {

    const int S1 = 4 , S2 = 5 ;
    
    int no1[S1] = { 42 ,  4 , 27 ,  8 };
    int no2[S2] = { 20 , 91 , 12 , 55 , 39 };

    vector<int>  no ;
    
    // 將兩陣列依個位數由小到大合併加入 no 向量陣列
    merge( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) , 
           cmp_last_digit ) ;
    
    // 列印
    copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}
