#include <iostream>
#include <iomanip>

using namespace std ;

int main() {

   int  i , j ;

   for ( i = 1 ; i < 10 ; ++i ) {
      for ( j = 1 ; j < 10 ; ++j ) {
         // setw(2) 表示緊接在後的資料用 2 格的寬度印出  
         cout << j << 'x' << i << "=" << setw(2) << i*j << " " ;
      }
      cout << '\n' ;
   }

   return 0 ;
   
}

