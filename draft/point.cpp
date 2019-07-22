#include "point.h"

Coordinate::Coordinate():
  _x(),_y(){
      if(!areValid())
        throw std::invalid_argument("wrong");
}

Coordinate::Coordinate(int x,int y):
  _x(x),_y(y){
      if(!areValid())
      throw std::invalid_argument("wrong");
  }


bool Coordinate::areValid() const {
   if (_x<300000000&&_y<300000000)
     return true;
  else
     return false;   
}

 std::ostream& operator <<(std::ostream& os, const Coordinate& pt){
     os<<"("<<pt.x()<<","<<pt.y()<<")";
     return os;
 }
 


 bool operator<(const Coordinate &c1, const Coordinate &c2){
     if(c2.x()!=c1.x()&&c2.y()!=c1.x()) return c1.x() < c2.x()||c1.x()==c2.x()&&c1.y()<c2.y();
}