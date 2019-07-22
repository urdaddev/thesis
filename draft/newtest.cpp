#include <iostream>
#include <armadillo>
#include <omp.h>
#include <bits/stdc++.h>
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

int main(){

std::map<Coordinate, double> mytable; 

mytable.insert(std::pair<Coordinate,double>({1,0},1.1));
mytable.insert (std::pair<Coordinate,double>({0,2},3.2));  // max efficiency inserting
mytable.insert ( std::pair<Coordinate,double>({1,0},1.2)); 
mytable.insert (std::pair<Coordinate,double>({1,0},10)); 

    for (const auto &entry:mytable) { 
      auto key =entry.first;

        std::cout<< "("<<key.x <<","<<key.y<< ") \n " << entry.second << '\n';
    } 






 //
}
