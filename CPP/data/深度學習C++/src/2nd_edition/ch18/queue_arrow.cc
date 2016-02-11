#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std ;

int main() {

    int           i ;
    const int     NO = 4 ;
    string  contestant[NO] = { "化端" , "窥毖" , "甝反" , 
                               "篟" };
    
    // 纗Θ罿だ计
    queue<int>  score ;

    // 砞﹚睹计贺
    srand( static_cast<unsigned>(time(NULL)) ) ;

    // 繦種玻ネ计 score 
    for ( i = 0 ; i < NO ; ++i )  score.push(rand()%11) ;

    // パ score だ计
    i = 0 ;
    while ( ! score.empty() ) {
        cout << score.front() << " : " << contestant[i++] << "    " ;     
        score.pop() ;
    }
    cout << endl ;
    
    return 0 ;
}
