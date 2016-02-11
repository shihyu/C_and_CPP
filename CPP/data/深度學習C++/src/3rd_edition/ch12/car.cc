#include <iostream>
#include <vector>
#include <string>

using namespace std ;

typedef  string  Name ;
typedef  string  Location ;


// 汽車類別
class  Car {

  protected :

    // 乘客人數
    int  passenger_no ;                   

    // 建構函式
    Car( int n = 0 )  : passenger_no(n) {}

  public :

    // 指定虛擬運算子與列印虛擬函式
    virtual Car&  operator=( const Car& foo ) = 0 ;
    virtual ostream&  print( ostream& out ) const = 0 ;

    // 乘客數目
    int  passenger() const {  return passenger_no ;  }

    // 虛擬解構函式
    virtual ~Car() {}

} ;

// 覆載輸出運算子
ostream&  operator<< ( ostream& out , const Car& foo ) {
    return  foo.print(out) ;
}

// 休旅車類別 
class  RV :  public  Car {

  private :

    Location   place ;   // 探勘處所

  public :

    // 建構函式
    RV( Location p , int no = 0 ) : Car(no) , place(p) {}

    // 指定建構函式
    RV&  operator= ( const RV& foo ) {
        place        = foo.place ;
        passenger_no = foo.passenger_no ;
        return  *this ;
    }

    // 指定建構函式
    RV&  operator= ( const Car& foo ) {
        return  operator=( dynamic_cast<const RV&>(foo) ) ;
    }

    // 列印
    ostream&  print( ostream& out ) const {
        return  out << "> 休旅車   \t"
                    << "  乘客   : " << passenger_no << " 人\t\t" 
                    << "  旅遊地 : " << place ;
    }

} ;

// 豪華禮車類別
class  Limousine : public  Car {

  private :

    Name   driver ;      // 司機

  public :

    // 建構函式
    Limousine( Name d , int no = 0 ) : Car(no) , driver(d) {}

    // 指定建構函式 : 另一種處理方式
    Limousine&  operator= ( const Car& car ) {
        const Limousine  *lm = 
            dynamic_cast<const Limousine*>(&car) ;
        if ( lm ) {
            driver = lm->driver ;
            passenger_no = lm->Car::passenger_no ;
        }
        return *this ;
    }
    
    // 列印
    ostream&  print( ostream& out ) const {
        return  out << "> 豪華禮車 \t" 
                    << "  乘客   : " << passenger_no << " 人\t\t" 
                    << "  司機   : " << driver ;
    }

};

// 所有的乘座 RV 的乘客總數
int  total_RV_passengers( const vector<Car*>& foo ) {

    RV*  rv ;
    int  no = 0 ;

    // 檢查陣列, 若為指向 RV, 則將其人數加入
    for ( int i = 0 ; i < foo.size() ; ++i ) {
        rv = dynamic_cast<RV*>(foo[i]) ;
        if ( rv ) no += rv->passenger() ;
    }
    return  no ;

}

// 將陣列中所有的 RV 資料重新設定
void  setup_RV_data( vector<Car*>&  foo , Location  place ) {

    Car  *new_rv = new RV(place) ;

    // 將是 RV 的資料取出, 重新設定
    for ( int i = 0 ; i < foo.size() ; ++i ) *foo[i] = *new_rv ;

    delete  new_rv ;
    
}

int main() {

    int  i ;
    
    // 指標向量陣列
    vector<Car*>  cars ;     

    cars.push_back( new RV("花蓮",5) ) ;
    cars.push_back( new Limousine("張三",4) ) ;
    cars.push_back( new RV("墾丁",5) ) ;
    cars.push_back( new RV("淡水",3) ) ;
    cars.push_back( new Limousine("李四",8) ) ;
    
    // 列印所有汽車資料
    for ( i = 0 ; i < cars.size() ; ++i ) 
        cout << *cars[i] << endl ;

    // 列印 RV 總乘客人數
    cout << "> RV 總乘客人數 : " << total_RV_passengers(cars) 
         << "\n\n" ;

    // 重新設定 RV 資料, 與列印
    setup_RV_data( cars , "" ) ;
    for ( i = 0 ; i < cars.size() ; ++i ) 
        cout << *cars[i] << endl ;
    
    // 清除所有動態資料
    for ( i = 0 ; i < cars.size() ; ++i ) delete  cars[i] ;

    return 0 ;
    
}
