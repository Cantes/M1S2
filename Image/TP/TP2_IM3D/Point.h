#ifndef POINT_H
#define POINT_H



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


     void afficher ();

private :
    double x;
    double y;
    double z;


};
#endif
