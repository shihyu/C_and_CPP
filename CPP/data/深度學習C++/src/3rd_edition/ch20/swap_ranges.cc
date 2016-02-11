#include <iostream>
#include <algorithm>
#include <string>

using namespace std ;

int main() {
    
    string  foo = "TREK" ;
    string  bar = "startrek" ;
    
    cout << "對調前 : " << foo << " " << bar << endl ;
    swap_ranges( foo.begin() , foo.end() , bar.begin()+4 ) ;
    cout << "對調後 : " << foo << " " << bar << endl ;

    return 0 ;
    
}

    
