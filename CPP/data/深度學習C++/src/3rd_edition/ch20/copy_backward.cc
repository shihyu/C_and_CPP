#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std ;

int main() {
    
    int          no[8] = { 2 , 1 , 8 , 7 , 4 , 3 , 5 , 9 };
    deque<int>   foo(10,0) ;   // 10 個 0 

    // 將 no[1] .. no[3] 三個元素覆蓋在 foo 佇列, 
    // 且其右邊界為 foo.end()-2, 即倒數第二個元素
    //
    copy_backward( no+1 , no+4 , foo.end()-1 ) ;

    // 使用 ostream_iterator 將 foo 的資料全部輸出到螢幕
    copy( foo.begin() , foo.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;

}

            
