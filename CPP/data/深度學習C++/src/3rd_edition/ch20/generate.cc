#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std ;

// 计ㄧΑン摸
struct  Sequence {

    // 计癬﹍籔患糤
    int  no , step ;  

    Sequence( int a = 0 , int s = 1 ) : no(a) , step(s) {}

    int  operator() ()  {
        int s = no ;
        no += step ;
        return s ;
    }

};


int main() {

    // a Τ 5 ゼ﹚俱计
    vector<int>  a(5) ;

    // 盢 a 砞﹚Θ : 1 2 3 4 5 
    generate(a.begin(),a.end(),Sequence(1,1)) ;

    //  a 
    copy(a.begin(),a.end(),ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 盢 a ソЮ 4 3 2 1 单计
    generate_n(back_inserter(a),4,Sequence(4,-1)) ;

    //  a 
    copy(a.begin(),a.end(),ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    return 0 ;
}

