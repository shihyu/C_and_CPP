#include <iostream>
#include <vector>
#include <iomanip>

using namespace std ;

// 樂透包牌程式
void print_combination( const vector<int>& number , 
                        vector<int>& chosen_no , 
                        int depth , int start_index ) {

    int i ;
    static  int  count = 0 ;

    // 當遞迴的深度與找到的號碼數相同
    if ( depth == chosen_no.size() ) {

        // 輸出數字組合
        cout << setw(3) << ++count << " : " ;
        for ( i = 0 ; i < chosen_no.size() ; ++i ) 
            cout << setw(4) << chosen_no[i] ;
        cout << endl ;

    } else {

        // 遞迴式迴圈, 深一層的遞迴初始下標值會自動加一
        for ( i = start_index ; i < number.size() ; ++i ) {
            chosen_no[depth] = number[i] ;
            print_combination( number , chosen_no , depth+1 , i+1 ) ;
        }
        
    }
    
}

int main() {
    
    int  no ;
    cout << "> 輸入總號碼數量 : " ;
    cin  >> no ;

    // number  : 儲存所有的號碼
    vector<int>  number(no)  ;

    cout << "> 輸入 " << no << " 個號碼 : " ;
    for ( int i = 0 ; i < no ; ++i ) cin >> number[i] ;

    cout << "> 輸入包牌碼數量 : " ;
    cin  >> no ;

    // chosen_no  : 已找到的號碼
    vector<int>  chosen_no(no) ;

    // depth       : 遞迴深度
    // start_index : 遞迴迴圈中的初始下標值
    int  depth = 0 , start_index = 0 , count = 0 ;
    print_combination( number , chosen_no , depth , start_index ) ;

    return 0 ;
    
}
        
