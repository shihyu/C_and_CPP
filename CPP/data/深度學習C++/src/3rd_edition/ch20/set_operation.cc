#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std ;

int main() {
    
    const  int  S1 = 8 , S2 = 6 ;
    int  no1[S1] = { 73 , 44 , 23 , 19 , 37 , 65 , 44 , 44 };
    int  no2[S2] = { 25 , 23 , 44 , 20 , 10 , 87 };

    // 依數字大小由小到大重新排序
    sort(no1,no1+S1) ;    
    sort(no2,no2+S2) ;
    
    cout << "> 甲集合   : " ;
    copy( no1 , no1+S1 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;
    cout << "> 乙集合   : " ;
    copy( no2 , no2+S2 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    vector<int>  no ;

    // 計算交集, 並將結果插入向量 no
    set_intersection( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) ) ;
    
    cout << "> 交集     : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 重設陣列長度為 0
    no.resize(0) ;
    
    // 計算聯集, 並將結果插入向量 no
    set_union( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) ) ;
    cout << "> 聯集     : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 重設陣列長度為 0
    no.resize(0) ;

    // 計算差集, 並將結果插入向量 no
    set_difference( no1 , no1+S1 , no2 , no2+S2 , back_inserter(no) ) ;
    cout << "> 差集     : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 重設陣列長度為 0
    no.resize(0) ;

    // 計算對稱差集, 並將結果插入向量 no
    set_symmetric_difference( no1 , no1+S1 , no2 , no2+S2 , 
                              back_inserter(no) ) ;
    cout << "> 對稱差集 : " ;
    copy( no.begin() , no.end(), ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

    
