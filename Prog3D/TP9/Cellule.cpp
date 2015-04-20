#include "Cellule.h"


Cellule::Cellule(Point A, Point B, Point C, Point D){

	this->sommetA = A;
	this->sommetB = B;
	this->sommetC = C;
	this->sommetD = D;

}

double Cellule::getXMin(){
	return std::min(std::min(this->sommetA.getX(), this->sommetB.getX()),std::min(this->sommetC.getX(), this->sommetD.getX())); 
}

double Cellule::getYMin(){
	return std::min(std::min(this->sommetA.getY(), this->sommetB.getY()),std::min(this->sommetC.getY(), this->sommetD.getY())); 
}

double Cellule::getXMax(){
	return std::max(std::max(this->sommetA.getX(), this->sommetB.getX()),std::max(this->sommetC.getX(), this->sommetD.getX())); 
}

double Cellule::getYMax(){
	return std::max(std::max(this->sommetA.getY(), this->sommetB.getY()),std::max(this->sommetC.getY(), this->sommetD.getY())); 
}

Point Cellule::getSommetA(){
	return this->sommetA;
}

Point Cellule::getSommetB(){
	return this->sommetB;
}

Point Cellule::getSommetC(){
	return this->sommetC;
}

Point Cellule::getSommetD(){
	return this->sommetD;
}

bool Cellule::appartientCellule(Point p){

	if(p.getX() >= this->getXMin() && p.getX() <= this->getXMax() ){
		
		if(p.getY() >= this->getYMin() && p.getY() <= this->getYMax() ){
			return true;
		}else{
			return false;
		}
	
	}else{
		return false;
	}
}




