#include <iostream>

using namespace std ;

int main() {

    int   i , j ;
    
    char  a[30] = "塞外黃花，似金釘釘地。" ;
    char  b[30] = "京中白塔，如玉鑽鑽天。" ;
    
    char  c[60] ;

    // 複製第一個字串, 且保留空字元下標    
    for ( i = 0 ; a[i] != '\0' ; ++i )  c[i] = a[i] ;
    
    // 由第一個字串的空字元下標開始複製
    for ( j = 0 ; b[j] != '\0' ; ++j )  c[i+j] = b[j] ;
    
    // 補上空字元
    c[i+j] = '\0' ;
    
    cout << c << endl ;

    return 0 ;
    
}
