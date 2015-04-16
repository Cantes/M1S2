#ifndef Cellule_H
#define Cellule_H

#include "../TP1/Point.h"
#include <iostream>
#include <algorithm>

class Cellule{

	private :
		Point sommetA;
		Point sommetB;
		Point sommetC;
		Point sommetD;
		
	public :
		Cellule( Point A, Point B, Point C, Point D);
		
		
		double getXMin();
		double getXMax();
		double getYMin();
		double getYMax();
		
		Point getSommetA();
		Point getSommetB();
		Point getSommetC();
		Point getSommetD();
		
		bool appartientCellule(Point p);	
};


#endif
