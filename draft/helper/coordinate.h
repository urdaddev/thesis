#ifndef COORDINATE_H
#define COORDINATE_H

#include <map>
struct Coordinate
{
  int x;
  int y;
 
  Coordinate(int x,int y): 
    x(x),y(y)
    {
    }
  bool operator<(const Coordinate &p2) const
  {
     
        return x<p2.x||x==p2.x&&y<p2.y;
  }
  bool operator==(const Coordinate &p2) const
  {
      if((x==p2.x&&y==p2.y)||(y==p2.x&&x==p2.y))
      {
        return true;
      }
      else
      {
         return false;
      }
      
  }
};
#endif