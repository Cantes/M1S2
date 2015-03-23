#include "Point.h"

Point::Point(void){
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(long double x1, long double y1, long double z1){
	x = x1;
	y = y1;
	z = z1;
}

Point::Point(const Point& p){
	x = p.x;
	y = p.y;
	z = p.z;
}

Point::~Point(void){

}

long double Point::getX(void) const{
	return x;
}

long double Point::getY(void) const{
	return y;
}

long double Point::getZ(void) const{
	return z;
}

void Point::setX(long double x1){
	x = x1;
}

void Point::setY(long double y1){
	y = y1;
}

void Point::setZ(long double z1){
	z = z1;
}	

Point Point::projectOnLine(Point point1Line, Point point2Line){
	Vector v( (point2Line.getX()-point1Line.getX()), point2Line.getY()-point1Line.getY(), point2Line.getZ()-point1Line.getZ());
	return this->projectOnLine(v,point1Line);
}

Point Point::projectOnLine(Vector vecteur, Point pLine){
	long double norme = vecteur.norme();
	long double scalaire;
	long double taille;
	
	Vector v( (this->getX()-pLine.getX()), this->getY()-pLine.getY(), this->getZ()-pLine.getZ());
		
	scalaire = v.scalar(vecteur);	
	
	taille = scalaire / norme;	
	
	vecteur.normalize();
	
	return Point(pLine.getX()+vecteur.getX()*taille,pLine.getY()+vecteur.getY()*taille,pLine.getZ()+vecteur.getZ()*taille);
}

void Point::affiche(){
	cout << "(" << this->getX() << "," << this->getY() << "," << this->getZ() << ")" << endl;
}
