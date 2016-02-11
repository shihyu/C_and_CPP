#include <iostream>

using namespace std ;

int main() {

    int i , j ;
    const int row = 2 , col = 3 ;

    int a[row][col] = { { 1,2,3 } , { 4,5,6 } } ;
    
    // ¦C¦L a ¯x°}
    for ( i = 0 ; i < row ; ++i ) {
        for ( j = 0 ; j < col ; ++j ) {
            cout << a[i][j] << " " ;
        }
        cout << endl ;
    }

    cout << endl ;

    
    for ( i = 0 ; i < row ; ++i ) {

        cout << "a[" << i << "]   = " << a[i] << "  or  " 
             << "a+i  =  " << a+i << "  or  " 
             << "*(a+" << i << ")  = " << *(a+i) << endl ;

        for ( j = 0 ; j < col ; ++j ) {

            cout << " |-> a[" << i << "]+" << j 
                 << " = " << a[i]+j << "  or  " 
                 << "*(a+" << i << ")+" << j << " = " 
                 << *(a+i) + j << endl ;

            cout << "      |->  a[" << i << "][" << j << "] \t= " 
                 << a[i][j] << endl ;

            cout << "      |->  *(*(a+" << i << ")+" << j << ") \t= " 
                 << *(*(a+i)+j) << endl ;

            cout << "      |->  *(a[" << i << "]+" << j << ") \t= " 
                 << *(a[i]+j) << endl ;

            cout << "      |->  (*(a+" << i << "))[" << j << "] \t= " 
                 << (*(a+i))[j] << endl ;

        }
        cout << endl ;
    }
    
    cout << endl ;

}
