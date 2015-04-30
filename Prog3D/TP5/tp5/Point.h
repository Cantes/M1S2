#ifndef POINT_H
#define POINT_H
#include "Vector.h"



class Point
 {

public:



    //constructeurs
    Point();
    Point(double x, double y, double z);
    Point (const Point& p);

    //getteurs
     //getteurs
     double getX () const;
     double getY () const;
     double getZ () const;
  //setteurs
     void setX (double newX);
     void setY (double newY);
     void setZ (double newZ);

//projection
     Vector createVector (Point p);
     Point ProjectOnLine (Point p1, Point p2);
     Point ProjectOnLine (Vector vecteur, Point p);
     Point ProjectOnPlan (Point p, Vector v);

     //autres fonctions
     Point multiply (Vector v, double n);
     Point addit (Vector v);
     double distance(Point p);
     void afficher ();
     void drawPoint();

private :
    double x;
    double y;
    double z;


};
#endif
