#include <iostream>
#include <map>

struct xmap{
  int row; 
  int col;
  const double &xvalue; 
};

xmap Xmap [235000];

struct ymap {
   int i;
   int j; 
   const double &yvalue;
};

ymap Ymap [27612382500];

struct Point { double i, j; };
struct PointCmp {
    bool operator()(const Point& lhs, const Point& rhs) const { 
        return lhs.i < rhs.j; // NB. intentionally ignores y
    }
};
  //You could also use a lambda that is not dependent on local variables, like this:
auto cmpLambda = [](const Point &lhs, const Point &rhs) { return lhs.i < rhs.j; };
 std::map<Point, double, decltype(cmpLambda)> lookup(cmpLambda);
   std::map<Point, double, PointCmp> mylookup = {
      { {0, 0}, 0 },
  };
mylookup.insert({})
//auto cmpLambda = [&mylookup](const Point &lhs, const Point &rhs) { return mylookup[lhs] < mylookup[rhs]; };

 
   //Various ways of inserting elements:
