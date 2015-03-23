#include "Triangle.h"

Triangle::Triangle(Point A, Point B, Point C){
	
	this->sommetA = A;
	this->sommetB = B;
	this->sommetC = C;
}

Point  Triangle::getSommetA(){
	return this->sommetA;
}

Point  Triangle::getSommetB(){
	return this->sommetB;
}

Point  Triangle::getSommetC(){
	return this->sommetC;
}
