#ifndef Point_h
#define Point_h

#include <iostream>
#include <stdio.h>   
#include <stdlib.h>     
#include <math.h>

using namespace std;

class Point{

	private :
		float x;
		float y;
		float z;
	
	public :
		//Constructeurs, destructeur
		Point();
		Point(float x1, float y1, float z1);
		Point(const Point& p);
		~Point();
		
		//Getteurs, Setteurs
		float getX() const;
		float getY() const;
		float getZ() const;
		void setX(float x1);
		void setY(float y1);
		void setZ(float z1);
		 

};

#endif
