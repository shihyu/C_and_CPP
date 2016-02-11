#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std ;

// 比較個位數大小
bool  cmp_last_digit( int a , int b ) {   return  a % 10 < b % 10 ;  }

int main() {
    
    const  int  S1 = 8 , S2 = 6 ;
    int  no1[S1] = { 73 , 44 , 23 , 19 , 37 , 65 , 44 , 44 };
    int  no2[S2] = { 25 , 23 , 44 , 20 , 10 , 87 };

    vector<int>  no ;

    // 以個位數大小重新排序
    sort(no1,no1+S1,cmp_last_digit) ;
    sort(no2,no2+S2,cmp_last_digit) ;

    cout << "> 甲集合     : " ;
    copy( no1 , no1+S1 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;
    cout << "> 乙集合     : " ;
    copy( no2 , no2+S2 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;
    
    // 計算交集, 並將結果插入向量 no, 但並不使用個位數比較數字大小
    set_intersection( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) ) ;
    
    cout << "> 交集(錯誤) : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    no.resize(0) ;
    
    // 計算交集, 並將結果插入向量 no, 使用個位數方式比較大小
    set_intersection( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) , 
                      cmp_last_digit ) ;
    
    cout << "> 交集(正確) : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

    
