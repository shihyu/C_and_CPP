#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int  *i = new int ;
    int  *j = new int ;
    
    for ( *i = 1 ; *i < 10 ; ++(*i) ) {
        for ( *j = 1 ; *j < 10 ; ++(*j) ) {
            cout << *j << 'x' << *i << '=' 
                 << setw(2) << (*i) * (*j) << " " ;
        }
        cout << endl ;
    }

    delete i , j ;

    return 0 ;

}
