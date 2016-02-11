#include <iostream>

using namespace std ;

// ·h¶ê½Lµ{¦¡

void move_disc ( int no , char from , char to , char through ) {
    static int counter = 1 ;
    if ( no == 1 ) 
        cout << counter++ << " : " 
             << from << " --> " << to << endl ;
    else {
        move_disc( no-1 , from , through , to ) ;
        move_disc( 1    , from , to , through ) ;
        move_disc( no-1 , through , to , from ) ;
    }
}

int  main() {

    int  n = 3 ;

    move_disc( n , 'L' , 'R' , 'M' ) ;

    return 0 ;
    
}
