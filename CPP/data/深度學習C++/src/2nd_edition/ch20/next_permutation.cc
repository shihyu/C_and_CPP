#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std ;

int main() {
    
    int a , b , c , d , e , f ;
    const int S = 9 ;

    int no[S] = {1,2,3,4,5,6,7,8,9};
    
    do {
        a = no[0] ;        b = no[1] ;        c = no[2] ;

        if ( ! ( a < b && b < c ) ) continue ;

        d = no[3]*10+no[4] ;
        e = no[5]*10+no[6] ;
        f = no[7]*10+no[8] ;

        if ( a * e * f + b * d * f + c * d * e ==  d * e * f ) {
            cout << setw(3) << a << setw(7) << b << setw(7) << c << "\n" 
                 << "---- + ---- + ---- = 1" << "\n" 
                 << setw(3) << d << setw(7) << e << setw(7) << f << endl ;
        }

    } while ( next_permutation(no,no+S) ) ;
    
    return 0 ;
    
}

              
        
