#include "Point.h"

#include <math.h>
#include <iostream>

using namespace std;


Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double abcisse, double ordonnee,double hauteur)
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


void Point::afficher()
{
   cout<<x<<" "<<y<<" "<<z<<endl;
}
