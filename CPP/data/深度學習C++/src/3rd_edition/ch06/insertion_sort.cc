#include <iostream>
#include <vector>

using namespace std ;

int main() {

    int  i , j , no , tmp ;
    
    cout << "> 輸入資料個數 : "  ;
    cin >> no ;

    // 定義一 no 筆資料的向量陣列
    vector<int>  data(no) ;
    
    cout << "> 請輸入 " << no << " 個數字 : " ;
    for ( i = 0 ; i < data.size() ; ++i ) cin >> data[i]  ;

    // 執行插入排序
    for ( i = 1 ; i < data.size() ; ++i ) {
    
        // 往前對調直到數字較之前的元素大為止
        for ( j = i ; j > 0 ; --j ) {

            if ( data[j] >= data[j-1] ) 
                break ;
            else {
                // 若比之前的元素小則與之對調
                tmp       = data[j] ;
                data[j]   = data[j-1] ;
                data[j-1] = tmp ;
            } 

        }

    }

    // 輸出排序後的結果
    cout << "\n> 排序後結果 : " ;
    for ( i = 0 ; i < data.size() ; ++i ) cout << data[i] << " " ;
    cout << endl ;

    return 0 ;
    
}

