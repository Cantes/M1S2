#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../TP1/Vector.h"
#include "../TP1/Point.h"


Vector produitVectoriel(Vector v1, Vector v2){

	return v1.vetoriel(v2);

}

Vector normaleFace(Point v1, Point v2, Point v3){

	return	produitVectoriel(
		Vector(v2.getX()-v1.getX(),v2.getY()-v1.getY(),v2.getZ()- v1.getZ()), 
		Vector(v3.getX()-v1.getX(),v3.getY()-v1.getY(),v3.getZ()-v1.getZ())
				);
}	



int main(int argc, char *argv[]){

	Point v1(0, 9, -5);
	Point v2(-4, 5, -5);
	Point v3( -4, 5, 5);
	
	Vector v = normaleFace(v1, v2, v3);
	v.normalize();
	v.affiche();
	
	// Code de retour
	return 1;
}
