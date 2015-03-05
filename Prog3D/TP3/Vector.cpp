#include "Vector.h"
#include <math.h>
#include <iostream>"

using namespace std;

//constructeurs

Vector::Vector()
{
    x = 1;
    y = 1;
    z = 1;
}

Vector::Vector(double vx, double vy, double vz)
{
x = vx;
y = vy;
z = vz;
}


Vector::Vector (const Vector& vect){
x = vect.x;
y = vect.y;
z = vect.z;
}

//getteurs
double Vector::getX(){
return x;
}

double Vector::getY(){
return y;
}

double Vector::getZ(){
return z;
}

//setteurs
void Vector::setX(double newX){
x = newX;
}

void Vector::setY(double newY){
y = newY;
}

void Vector::setZ(double newZ){
z = newZ;
}

//norme
double Vector::Norme(){
double norme = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
return norme;
}

void Vector::Normalized(){
x = x/Norme();
y = y/Norme();
z = z/Norme();
}

double Vector::Scalar(Vector v){
return x*v.x+y*v.y+z*v.z;
}


Vector Vector::vectoriel(Vector v)
{
    Vector produit = Vector(((y*v.z)-(z*v.y)),((z*v.x)-(x*v.z)),((x*v.y)-(y*v.x)));
    return produit;
}

double Vector::angle(Vector v)
{
    double cosinus;
    cosinus = Norme()/v.Norme();
   //double cosinus = scalar(vector2)/(vector2.norme() * norme());
    return acos(cosinus);
}

Vector::~Vector()
{
    //dtor
}

void Vector::afficher()
{
   cout<<x<<" "<<y<<" "<<z<<endl;

}
