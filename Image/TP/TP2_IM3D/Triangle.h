#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "Point.h"
#include <string>


 using namespace std;
class Triangle{


public :

    Point p0;
    Point p1;
    Point p2;

    Triangle(Point p0, Point p1, Point p2);


void toString( std::ostream& os);



};



#endif
