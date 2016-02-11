#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

class  Bitmap {
  private :
    
    string  filename ;
    
  public :

    Bitmap( const string& f ) : filename(f) {} ;

    bool  convert_file() const {

        string         out = filename + ".dat" ;
        ifstream       infile(filename.str()) ;
        ofstream       outfile(out) ;
        string         line ;
        istringstream  istr ;
        char           bits ;
        
        while ( getline(infile,line) ) {
            if ( line[0] == '#' ) continue ;
            istr.str(line) ;
            while ( istr >> bits ) outfile << bits ;
            istr.clear() ;
        }
        
    }
    
    

};

int main() {

    


    return 0 ;
}

