#include <iostream>
#include <iomanip>
#include <string>

using  namespace  std ;

const  int  MAX_CLASS  = 3  ;   // 班別最大數目
const  int  MAX_STUDENT = 10 ;  // 每個班別學生最大數目

// 學生資料結構 : 姓名與學號
struct  Student {
    string  name ;
    int     id   ;
};

// 覆載學生資料型別的輸入運算子
istream&  operator>> ( istream& in  , Student& s ) {
    return  in >> s.name >> s.id ;
}

// 覆載資料型別的輸出運算子
ostream&  operator<< ( ostream& out , const Student& s ) {
    return  out << setw(6) << s.name.c_str() << " [" <<  s.id 
                << "]" ;
}

// 班別類別
class  Class {
  private :
    
    // 班別內的學生名單與人數
    Student   student[MAX_STUDENT] ;
    int       student_no ;
    
  public :
    
    // 建構函式
    Class() : student_no(0) {}
    
    // 加入一個學生到班別內
    bool  insert_student( const Student& s ) { 
        if ( student_no == MAX_STUDENT )
            return  false ;
        else {
            student[student_no++] = s ;  
            return  true ;
        }
    }

    // 班別現在的學生人數
    int  current_student_no() const { return student_no ; }
    
    // 覆載班別類別的輸出運算子
    friend ostream& operator<< ( ostream& out , const Class& foo ){
        for ( int i = 0 ; i < foo.student_no ; ++i ) {
            out << i+1 << " : " << foo.student[i] << "\n" ;
        }
        return out ;
    }
    
};

// 課程類別
class  Course {

  private :

    // 每一課程的班別陣列
    Class  classes[MAX_CLASS] ;

  public :

    // 加入一個學生對某一個班別
    bool  add_student( int c , const Student& s ) {
        if ( c < 1 || c > MAX_CLASS ) return false ;
        return ( classes[c-1].insert_student(s) ? true : false ) ; 
    }

    // 覆載課程的輸出運算子
    friend  ostream&  operator<< ( ostream& out , 
                                   const Course& foo ) {

        int  total_student_no = 0 ;

        for ( int i = 0 ; i < MAX_CLASS ; ++i ) {
            total_student_no += foo.classes[i].current_student_no() ;
            out << "第 " << i+1 << " 班" << " : \n"
                << left << foo.classes[i] << "\n" ;
        }
        out << "總修課人數 : " << total_student_no << endl ;
        
        return out ;
    }

};


int  main() {

    Course   foo ;  // 課程物件
    int      c ;    // 班別
    Student  s ;    // 學生

    // 輸入班別與學生資料到課程物件內, 鍵入 0 結束輸入
    cout << "> 輸入班別, 姓名, 學號 : \n" ;
    while ( 1 ) {
        cin >> c ;
        if ( c == 0 ) break ;
        cin >> s ;
        foo.add_student(c,s) ;
    }

    // 列印全部修課班別學生
    cout << "\n" << foo << endl ;

    return 0 ;
    
}

        
    
    
