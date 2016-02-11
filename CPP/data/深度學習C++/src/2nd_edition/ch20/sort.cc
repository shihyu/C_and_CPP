#include <iostream>
#include <algorithm>
#include <string>

using namespace std ;

bool  case_insensitive( char a , char b ) {
    if ( a >= 'a' ) a = a - 'a' + 'A' ;
    if ( b >= 'a' ) b = b - 'a' + 'A' ;
    return  a < b ;
}

int main() {
    
    string  borg = "You Too Will Be Assimilated" ;
    
    cout << "> 排序前 : " << borg << endl ;

    sort( borg.begin() , borg.end() ) ;
    cout << "> 排序後 : " << borg << " (字母大小寫有別)" << endl ;

    sort( borg.begin() , borg.end() , case_insensitive ) ;
    cout << "> 排序後 : " << borg << " (字母大小寫無關)" << endl ;
}

