#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std ;

int main() {
    
    int          no[8] = { 2 , 1 , 8 , 7 , 4 , 3 , 5 , 9 };
    deque<int>   foo(10,0) ;   // 10 個 0 

    // 複製 no 前五個元素到 foo 的第四個位置之後
    copy( no , no+5 , foo.begin()+3 ) ;

    // 將 no[4] .. no[6] 由 foo 的前端一一插入
    copy( no+4 , no+7 , front_inserter(foo) ) ;

    // 使用 ostream_iterator 將 foo 的資料全部輸出到螢幕
    copy( foo.begin() , foo.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;

}

            
