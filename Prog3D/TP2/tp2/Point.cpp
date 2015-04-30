#include "Point.h"
#include "Vector.h"
#include <math.h>
#include <iostream>"

using namespace std;


Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double abcisse, double ordonnee, double hauteur)
{
    x = abcisse;
    y = ordonnee;
    z = hauteur;
}

Point::Point(const Point& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

//méthodes

//getteurs
double Point::getX() const{
return x;
}


double Point::getY() const{
return y;
}

double Point::getZ() const{
return z;
}

//setteurs
void Point::setX(double newX){
x=newX;
}

void Point::setY(double newY){
y=newY;
}

void Point::setZ(double newZ){
z=newZ;
}

//projection
//create vector
Vector Point::createVector(Point pt){
double abs = pt.x - x;
double ord = pt.y - y;
double hau = pt.z - z;
Vector vec (abs, ord, hau);
return vec;
}

Point Point::ProjectOnLine(Point pt1, Point pt2){
    Point projection = Point();
    Vector vectU = pt1.createVector(pt2);
   // Vector vectU = Vector(pt2.x-pt1.x, pt2.y-pt1.y, pt2.z- pt1.z);
   projection = ProjectOnLine(vectU,pt1);
   /* Vector vectAB = Vector(x- pt1.x, y - pt1.y, z - pt1.z); // pt1.createVector(this);


    double normeProj = (vectAB.Scalar(vectU))/vectU.Norme();

    vectU.Normalized();

    projection.x = pt1.getX()+ vectU.getX()* normeProj;
    projection.y = pt1.getY()+ vectU.getY()* normeProj;
    projection.z = pt1.getZ()+ vectU.getZ()* normeProj;*/

    return projection;
}

Point Point::ProjectOnLine(Vector v, Point p)
{
    Point projection = Point();

    Vector vectab = Vector (x- p.x, y - p.y, z - p.z);

    double normeProj = vectab.Scalar(v)/v.Norme();

    v.Normalized();

    projection.setX(p.getX()+ v.getX()* normeProj) ;
    projection.setY(p.getY()+ v.getY()* normeProj) ;
    projection.setZ(p.getZ()+ v.getZ()* normeProj) ;

    return projection;
}

Point Point::ProjectOnPlan(Point p, Vector v)
{
    Point projection = Point();

    Vector am = Vector(x-p.getX(), y-p.getY(), z-p.getZ());
    double normeMM = am.Scalar(v)/v.Norme();

    projection.x = x+ v.getX()* normeMM;
    projection.y = y+ v.getY()* normeMM;
    projection.z = z+ v.getZ()* normeMM;

    return projection;
}

Point Point::multiply (Vector v, double n)
 {
     double a = (v.getX()*n)+x;
     double b = (v.getY()*n)+y;
     double c = (v.getZ()*n)+z;

     Point p = Point(a,b,c);
     return p;
 }

   Point Point::addit (Vector v)
   {
      double a = v.getX()+x;
     double b = v.getY()+y;
     double c = v.getZ()+z;

     Point p = Point(a,b,c);
     return p;
   }
void Point::afficher()
{
   cout<<x<<" "<<y<<" "<<z<<endl;

}
