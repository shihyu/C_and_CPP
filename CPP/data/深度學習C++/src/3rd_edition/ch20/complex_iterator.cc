#include <iostream>
#include <complex>     // 使用複數模板類別
#include <iterator>

using namespace std ;

int main() {

    complex<double>  c , sum = 0 ;

    cout << "輸入 : " ;

    istream_iterator< complex<double> >  iter(cin) ;

    // 持續加入複數資料  直到收到終結字元為止
    for ( ; iter != istream_iterator< complex<double> >() ; iter++ ) 
        sum += *iter ;
    
    cout << "總和 : " << sum << endl ;
    
}

