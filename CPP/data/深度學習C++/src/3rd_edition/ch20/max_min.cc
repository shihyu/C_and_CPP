#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std ;

// ゑ耕埃 n 緇计
struct big_n {
    int n ;
    big_n( int a ) : n(a) {}
    bool  operator() ( int a , int b ) const {
        return a % n < b % n ;
    }
};

int main() {
    
    const int S = 10 ;
    int no[S] = { 3 , 4 , 5 , 7 , 8 , 1 , 9 , 3 , 4 , 1 };
    
    // 皚т程籔程じ
    cout << "> 皚 : " ;
    copy( no , no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl 
         << "> 程 : " << *min_element(no,no+S) << endl 
         << "> 程 : " << *max_element(no,no+S) << endl 
         << "> 砆 3 埃緇计程 : " 
         << *min_element(no,no+S,big_n(3)) << endl 
         << "> 砆 3 埃緇计程 : " 
         << *max_element(no,no+S,big_n(3)) << endl 
         << "> 砆 5 埃緇计程 : " 
         << *min_element(no,no+S,big_n(5)) << endl 
         << "> 砆 5 埃緇计程 : " 
         << *max_element(no,no+S,big_n(5)) << endl ;

    return 0 ;
    
}
