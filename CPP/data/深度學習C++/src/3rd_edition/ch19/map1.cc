#include <iostream>
#include <map>

using namespace std ;

int main() {

    map< char , int >            no ;
    map< char , int >::iterator  iter ;

    char * dna = "ACGTAAGTCCGAGTAATAGA" ;
    
    // 計算各個鹽基的次數
    for ( int i = 0 ; i < 20 ; ++i ) no[ dna[i] ] += 1 ;

    // 列印各個鹽基的總次數
    for ( iter = no.begin() ; iter != no.end() ; ++iter )
        cout << iter->first << " : " << iter->second << endl ;

    return 0 ;
}
