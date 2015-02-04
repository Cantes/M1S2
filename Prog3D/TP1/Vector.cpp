#include "Vector.h"
#include <math.h>

Vector::Vector(void){
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(double x1, double y1, double z1){
	x = x1;
	y = y1;
	z = z1;
}

Vector::Vector(const Vector& v){
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector::~Vector(void){

}

double Vector::getX(void) const{
	return x;
}

double Vector::getY(void) const{
	return y;
}

double Vector::getZ(void) const{
	return z;
}

void Vector::setX(double x1){
	x = x1;
}

void Vector::setY(double y1){
	y = y1;
}

void Vector::setZ(double z1){
	z = z1;
}	

double Vector::norme(void){
	return sqrt((x * x) +(y *y)+(z*z));
}

void Vector::affiche(){
	cout << this->getX() << "," << this->getY() << "," << this->getZ() << endl;
}

void Vector::normalize(){
	double norme = this->norme();
	x = x / norme;
	y = y / norme;
	z = z / norme;
}

double Vector::scalar(Vector vecteur2){
	return ((x * vecteur2.getX()) + (y * vecteur2.getY()) + (z * vecteur2.getZ()) );
}

Vector Vector::vetoriel(Vector vecteur2){
	double i,j,k;
	
	i = ( (y * vecteur2.getZ()) - (z * vecteur2.getY()) );
	j = ( (z * vecteur2.getX()) - (x * vecteur2.getZ()) );
	k = ( (x * vecteur2.getY()) - (y * vecteur2.getX()) );
	
	return Vector(i,j,k);
}

double Vector::angle (Vector vecteur2){
	return acos((this->scalar(vecteur2) / (this->norme() * vecteur2.norme()) ));
}
