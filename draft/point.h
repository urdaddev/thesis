 #ifndef COORDINATE_H
 #define COORDINATE_H
 #include <iostream>
 #include <string>
 #include <cmath>
 #include <map>
 #include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>


class Coordinate {
    public:
 
     Coordinate();
 
     Coordinate(int x,int y);
 
     int x() const { return _x;}
 
     int y() const { return _y ;};
     bool areValid() const;
    // bool operator ==(const Coordinate& p2) const;
    // bool operator !=(const Coordinate& p2) const;
 
 private:
     /* Instance variables */
     int _x;                       /* The x-coordinate of the point */
     int _y;                       /* The y-coordinate of the point */
    

};
std::ostream& operator<<(std::ostream &output, const Coordinate &c);
bool operator<(const Coordinate &c1, const Coordinate &c2);

#endif