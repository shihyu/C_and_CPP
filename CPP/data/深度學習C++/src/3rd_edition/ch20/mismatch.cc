#include <iostream>
#include <algorithm>

using namespace std ;

int main() {
    
    const int S = 10 ;
    int  foo[S] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 };
    int  bar[S] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 3 , 8 , 9 };

    pair<int*,int*>   ptr_pair ;

    // 在兩陣列內分別找尋首位不相同的元素位址
    ptr_pair = mismatch( foo , foo+S , bar ) ;

    if ( ptr_pair.first == foo+S ) {
        cout << "> 在 foo 陣列內找不到不一樣的元素 " << endl ;
    } else {
        cout << *(ptr_pair.first) << endl ;
    }

    if ( ptr_pair.second == bar+S ) {
        cout << "> 在 bar 陣列內找不到不一樣的元素 " << endl ;
    } else {
        cout << *(ptr_pair.second) << endl ;
    }

    return 0 ;
    
}
