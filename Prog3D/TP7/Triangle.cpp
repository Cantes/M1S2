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

bool Triangle::compareTriangle(Triangle t){
	return (this->getSommetA().compare(t.getSommetA()) && this->getSommetB().compare(t.getSommetB()) && this->getSommetC().compare(t.getSommetC()) );
}

std::vector<Point> Triangle::getSommets(){

	std::vector<Point> sommets;
	
	sommets.push_back(this->getSommetA());
	sommets.push_back(this->getSommetB());
	sommets.push_back(this->getSommetC());
	
	return sommets;

}
