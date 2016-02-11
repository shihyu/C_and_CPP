#include <iostream>
#include <vector>

using namespace std ;

//  虏虫礟祘Α : パ m 计い, ┮Τパ计舱
int main() {
    
    int  i , j , k , m , c = 1 ;
    
    cout << "> 计计 : " ;
    cin  >> m ;
    vector<int>  number(m) ;

    cout << "> ㄌΩ块 " << m << " 计 : " ;
    for ( i = 0 ; i < m ; ++i ) cin >> number[i] ;

    cout << endl ;

    // 琵 i , j , k ッ环ぃ穦单    
    for ( i = 0 ; i < m ; ++i ) {
        for ( j = i + 1 ; j < m ; ++j ) {
            for ( k = j + 1 ; k < m ; ++k ) {
                cout << c++ << " : " << number[i] << " " 
                     << number[j] << " " << number[k] << endl ;
            }
        }
    }

    return 0 ;
    
}

        
