#include "Point.h"

Point::Point(){
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(float x1, float y1, float z1){
	x = x1;
	y = y1;
	z = z1;
}

Point::Point(const Point& p){
	x = p.x;
	y = p.y;
	z = p.z;
}

Point::~Point(){

}

float Point::getX() const{
	return x;
}

float Point::getY() const{
	return y;
}

float Point::getZ() const{
	return z;
}

void Point::setX(float x1){
	x = x1;
}

void Point::setY(float y1){
	y = y1;
}

void Point::setZ(float z1){
	z = z1;
}	
