#include <iostream>
#include <vector>
#include <string>

using namespace std ;

// 列舉型別 : 可能的學院
enum  Colleges  { Sci , Eng , Mgt , Ife , Eth };

typedef  string  Name ;

// 學院 : 抽象基礎類別
class  College {
    
  protected :
    
    Name              name  ;        // 學院名稱
    vector<Name>      depts ;        // 學院內的學系
    
  public :

    // 列印學院共同必修 : 純虛擬函式
    virtual  void  list_common_subjects() const = 0 ;
    
    // 列印學院內所有的學系
    void  list_all_departments() const {
        cout << "> " << name << " :  "  ;
        for ( int i = 0 ; i < depts.size() ; ++i ) 
            cout << depts[i] << "  "  ;
        cout << endl ;
    }

    // 學院名稱
    Name get_college_name() const { return name ;  }
    
    // 學院內的學系總數
    int  get_dept_no() const { return depts.size()  ; }

    // 虛擬解構函式
    virtual  ~College() {}

};


// 列印預設的共同必修
void  College::list_common_subjects() const {
    cout << "  " << name << "共同必修科目 : 無" << endl ;
}



// 理學院
class  Science : public  College {
    
  public :

    // 建構函式
    Science() {
        name = "理學院" ; 
        depts.push_back( "數學系" ) ;   
        depts.push_back( "化學系" ) ;
        depts.push_back( "物理系" ) ;   
        depts.push_back( "生命科學系" ) ;
    }

    // 列印共同必修科目
    void  list_common_subjects() const {
        cout << "  " << name << "共同必修科目 : 微積分, 物理" 
             << endl ;
    }

        
};

// 工學院
class  Engineering : public  College {
    
  public :

    // 建構函式
    Engineering() {
        name = "工學院"  ; 
        depts.push_back( "土木系" ) ; depts.push_back( "機械系" ) ;
        depts.push_back( "化工系" ) ;
    }

    // 列印共同必修科目 : 使用預設的
    void  list_common_subjects() const { 
        College::list_common_subjects() ; 
    }

    
};


// 大學類別
class  University {

  private :

    Name               name ;            // 大學名稱
    vector<College*>   colleges ;        // 大學內的學院
    
  public :
  
    // 預設建構函式
    University() : name("聯邦星際大學") {
        colleges.push_back( new Science ) ; 
        colleges.push_back( new Engineering ) ;
    }

    // 解構函式 
    ~University() {  
        for ( int i = 0 ; i < colleges.size() ; ++i ) 
            delete colleges[i] ; 
    }
    
    // 列印所有學院名稱
    void  list_all_colleges() const {
        cout << "> " << name << "的學院 : "  ;
        for ( int i = 0 ; i < colleges.size() ; ++i ) 
            cout << colleges[i]->get_college_name() << "  " ;
        cout << endl ;
    }
    
    // 列印學校內的所有學系名稱
    void  list_all_departments() const {
        cout << "> " << name << "的學系 :\n" ;
        for ( int i = 0 ; i < colleges.size() ; ++i ) {
            cout << "<" << i+1 ;
            colleges[i]->list_all_departments() ;
        }
        cout << endl ;
    }

    // 學校名稱
    inline  Name  get_name() const { return name ;  }

    // 列印指定學院的所有學系名稱
    void  list_departments_in_college( const Colleges& college ) 
        const {
        colleges[college]->list_all_departments() ;
    }

    // 計算大學內所有學系的總數
    int  total_no_of_departments() const {
        int no = 0 ;
        for( int i = 0 ; i < colleges.size() ; ++i ) {
            no += colleges[i]->get_dept_no() ;
        }
        return no ;
    }
    
};


int  main() {

    Science  sci ;                  // 理學院物件                
    sci.list_all_departments() ;    // 列印理學院內的所有學系名稱
    sci.list_common_subjects() ;    // 列印理學院內的共同必修科目
    cout << endl ;

    Engineering  eng ;              // 工學院物件                
    eng.list_all_departments() ;    // 列印工學院內的所有學系名稱
    eng.list_common_subjects() ;    // 列印工學院內的共同必修科目
    cout << endl ;

    University  fed ;               // 大學物件
    fed.list_all_colleges() ;       // 列印大學內的所有學院名稱
    fed.list_all_departments() ;    // 列印大學內的所有學系名稱

    // 列印學系總數
    cout << "> " << fed.get_name() << "學系總數 = "           
         << fed.total_no_of_departments() << "\n\n" ;

    // 列印中央大學理學院內的所有學系
    fed.list_departments_in_college( Sci ) ;

    return 0 ;
    
}
