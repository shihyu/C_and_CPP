#include <iostream>
#include <climits>

using namespace std ;

int main() {

    // int 俱计程籔程
    cout << "> 程俱计 int \t\t\t: " 
         << numeric_limits<int>::max() 
         << "\n> 程俱计 int \t\t\t: " 
         << numeric_limits<int>::min() ;
    
    // unsigned int 礚腹俱计程籔程
    cout << "\n\n> 程礚腹俱计 unsigned int \t: " 
         << numeric_limits<unsigned int>::max() 
         << "\n> 程礚腹俱计 unsigned int \t: " 
         << numeric_limits<unsigned int>::min() ;
    
    // long long int 俱计程籔程
    cout << "\n\n> 程俱计 long long int \t: " 
         << numeric_limits<long long int>::max() 
         << "\n> 程俱计 long long int \t: " 
         << numeric_limits<long long int >::min() ;

    // float 虫弘絋疊翴计程籔程
    cout << "\n\n> 程虫弘絋疊翴计 float\t: " 
         << numeric_limits<float>::max() 
         << "\n> 程虫弘絋疊翴计 float\t: " 
         << numeric_limits<float>::min() ;

    // double 蛮弘絋疊翴计程籔程
    cout << "\n\n> 程蛮弘絋疊翴计 double\t: " 
         << numeric_limits<double>::max() 
         << "\n> 程蛮弘絋疊翴计 double\t: " 
         << numeric_limits<double>::min() << '\n' ;

    return 0 ;
    
}
