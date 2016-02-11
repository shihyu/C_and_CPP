#include <iostream>
#include <iterator>
#include <vector>

using namespace std ;

int main() {
    
    // 定義 foo 向量陣列存入 1 到 10 等十個整數
    vector<int>  foo ;
    for ( int i = 0 ; i < 10 ; ++i ) foo.push_back(i+1) ;
    
    // 設定一逆向迭代調整器物件, 且起始位址在末尾之後一位
    reverse_iterator< vector<int>::iterator >   riter(foo.end()) ;

    // 重複逆向往前, 每次印出資料後跳前兩個元素
    for( ; riter.base() > foo.begin() ; riter += 2 ) cout << *riter << " " ;
    cout << endl ;

    return 0 ;
    
}
