#include "Triangle.h"

#include <math.h>
#include <iostream>
#include<string>
#include <fstream>




Triangle::Triangle(Point pa,Point pb, Point pc){

p0 = pa;
p1 = pb;
p2 = pc;

}


void Triangle::toString( std::ostream& os){

/*p0.afficher();
p1.afficher();
p2.afficher();*/
                os <<"facet normal 0 0 0\n" ;
                os <<"outer loop\n";
                os << "vertex" << " " << p0.getX() << " " << p0.getY() << " " << p0.getZ() << "\n";
                os << "vertex" << " " << p1.getX() << " " << p1.getY() << " " << p1.getZ()<< "\n";
                os << "vertex" << " " << p2.getX() << " " << p2.getY() << " " << p2.getZ()<< "\n";
                os << "endloop\n ";
                os << "endfacet\n";


}






