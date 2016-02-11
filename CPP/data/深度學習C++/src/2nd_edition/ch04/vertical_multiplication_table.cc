#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int i , j  ;
    
    for ( i = 1 ; i <= 9 ; ++i ) {
        
        for ( j = 1 ; j <= 9 ; ++j ) cout << setw(6) << j ;
        cout << '\n' ;
        
        for ( j = 1 ; j <= 9 ; ++j ) cout << setw(4) << "x" 
                                          << setw(2) << i ;
        cout << '\n' ;
        
        for ( j = 1 ; j <= 9 ; ++j ) cout << setw(6) << "---" ;
        cout << '\n' ;
        
        for ( j = 1 ; j <= 9 ; ++j ) cout << setw(6) << i * j ;
        cout << "\n\n" ;
        
    }
    
    return 0 ;
    
}
