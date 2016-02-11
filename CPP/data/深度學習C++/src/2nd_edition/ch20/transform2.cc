#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <functional>

using namespace std ;

int main() {
    

    // data1 : 2 7 3 9 4 5 ,  data2 : 2 0 3 8 4 3
    ifstream  file1("data1") , file2("data2") ;
    ofstream  file3("data3") ;
 
    // 取出 data1 與 data2 檔案內整數, 直接將相乘後數字存入檔案 data3
    transform( istream_iterator<int>(file1) , istream_iterator<int>() ,
               istream_iterator<int>(file2) , 
               ostream_iterator<int>(file3," ") , multiplies<int>() ) ;
    
    return 0 ;
    
}

