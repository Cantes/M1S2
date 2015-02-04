#ifndef Vector_h
#define Vector_h

#include <iostream>
#include <iostream>
#include <stdio.h>

using namespace std;

class Vector{

	private :
		double x;
		double y;
		double z;
	
	public :
		//Constructeurs, destructeur
		Vector(void);
		Vector(double x1, double y1, double z1);
		Vector(const Vector& v);
		~Vector(void);
		
		//Getteurs, Setteurs
		double getX() const;
		double getY() const;
		double getZ() const;
		void setX(double x1);
		void setY(double y1);
		void setZ(double z1);
		
		//Methodes
		double norme();
		void normalize();
		double scalar(Vector vecteur2);
		Vector vetoriel(Vector vecteur2);
		double angle (Vector vecteur2);	
		void affiche(); 

};

#endif
