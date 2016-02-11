#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std ;

int main() {

    int i , j , n ;
    
    // 块簎近羆糷计
    cout << "> n : " ;
    cin >> n ;
    
    // 纗–竚紆痌计秖
    int  *ball = new int[n+1] ;

    // –竚癬﹍紆痌计 0
    for ( i = 0 ; i < n+1 ; ++i ) ball[i] = 0 ;

    // 代刚紆痌羆计秖
    const int M = 100000 ;

    srand( static_cast<unsigned int>(time(NULL)) ) ;

    int  position ;
    // 代刚 M Ω
    for ( i = 0 ; i < M ; ++i ) {

        // 璸衡紆痌竒筁 n 糷簎近竚
        position = 0 ;
        for ( j = 0 ; j < n ; ++j ) {
            // 璝睹计 1 玥瞴疾簎近┕, 玥┕オ
            if ( rand()%2 ) ++position ;
        }

        //  position 矪纗糤紆痌
        ++ball[position] ;

    }

    // だ计ゑよΑ挡狦, だダ s  2  n Ωよ
    int s = 1 ;
    for ( i = 0 ; i < n ; ++i ) s*=2 ;

    cout << "\n" ;
    for ( i = 0 ; i < n + 1 ; ++i )
        cout << "| " << static_cast<char>('A'+i) << " " ;
    cout << "|" << "\n\n" ;

    // ㄌだダ s , 穝秸俱–瑌瞴计, 块彼き计
    for ( i = 0 ; i < n + 1 ; ++i )
        cout << setw(3)
             << static_cast<unsigned>(1.*ball[i]*s/M+0.5) << " " ;
    cout << endl ;

    for ( i = 0 ; i < n + 1 ; ++i )  cout << setw(3) << " -- " ;
    cout << endl ;

    for ( i = 0 ; i < n + 1 ; ++i )  cout << setw(3) << s << " " ;
    cout << endl ;


    delete [] ball ;

    return 0 ;

}

