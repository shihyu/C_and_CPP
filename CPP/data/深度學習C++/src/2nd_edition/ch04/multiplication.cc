#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    // a : 砆计 , b : 计
    int  a , b , c , i , no ;

    cout << "> 叫块ㄢタ计 : " ;

    // 块 a , b 
    cin >> a >> b ;
    
    //  a X b Α场
    cout << "\n" 
         << setw(10) << a << endl 
         << setw(3)  << "x" << setw(7) << b << endl
         << setw(10) << "--------" << endl ;
    
    // 璸衡 b パ计癬–计(c), だ a 
    // i  : 北块竚
    // no : 纗计 b 狡埃 10 

    i = 0 ;
    no = b ;
    while ( no ) {
        c  = no % 10 ;
        no = no / 10 ;
        cout << setw(10-i) << c * a << endl ;
        ++i ;
    }
    
    // 程挡狦
    cout << setw(10) << "--------" << endl 
         << setw(10) << a * b << endl ;

    return 0 ;
    
}

        
