#ifndef Point_h
#define Point_h

#include "Vector.h"
#include <iostream>
#include <stdio.h>   
#include <stdlib.h>     
#include <math.h>

using namespace std;

class Point{

	private :
		double x;
		double y;
		double z;
	
	public :
		//Constructeurs, destructeur
		Point(void);
		Point(double x1, double y1, double z1);
		Point(const Point& p);
		~Point(void);
		
		//Getteurs, Setteurs
		double getX(void) const;
		double getY(void) const;
		double getZ(void) const;
		void setX(double x1);
		void setY(double y1);
		void setZ(double z1);
		
		//Methodes
		Point projectOnLine(Point point1Line, Point point2Line);
		Point projectOnLine(Vector vecteur, Point pLine);
		Point projectOnPlan(Point pointOnPlane, Vector normalOfPlane);
		void affiche();
		
		 

};

#endif
