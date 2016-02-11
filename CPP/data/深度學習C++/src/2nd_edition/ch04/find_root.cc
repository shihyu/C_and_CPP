#include <iostream>
#include <cmath>

using namespace std ;

int main() {

    //  a X^2 + b X + c = 0 
    float  a , b , c ;
    float  delta ;

    cout << "> 請依次輸入一元二次方程式的三個係數 : " ;

    cin >> a >> b >> c ;
    delta = b * b - 4. * a * c ;

    if ( delta >= 0. ) {

        // 實數根
        float  root1 , root2 ;
        root1 = ( -b + sqrt(delta) ) / ( 2. * a ) ;
        root2 = ( -b - sqrt(delta) ) / ( 2. * a ) ;
        cout << "root 1 : " << root1 << '\n' ;
        cout << "root 2 : " << root2 << '\n' ;

    } else {

        // 虛數根
        float  re , im ;
        re = -b / ( 2. * a ) ;
        im = sqrt(-delta) / ( 2. *a ) ;
        cout << "root 1 : " << re << " + " << im << " i" << endl ;
        cout << "root 2 : " << re << " - " << im << " i" << endl ;

    }

    return 0 ;
    
}
