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
		long double x;
		long double y;
		long double z;
	
	public :
		//Constructeurs, destructeur
		Point(void);
		Point(long double x1, long double y1, long double z1);
		Point(const Point& p);
		~Point(void);
		
		//Getteurs, Setteurs
		long double getX(void) const;
		long double getY(void) const;
		long double getZ(void) const;
		void setX(long double x1);
		void setY(long double y1);
		void setZ(long double z1);
		
		//Methodes
		Point projectOnLine(Point point1Line, Point point2Line);
		Point projectOnLine(Vector vecteur, Point pLine);
		Point projectOnPlan(Point pointOnPlane, Vector normalOfPlane);
		void affiche();
		bool compare(Point p);
		
		 

};

#endif
