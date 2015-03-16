#ifndef Voxel_h
#define Voxel_h

#include "../TP1/Point.h"

class Voxel{

	private:
		Point 	centre;
		double  rayon;
		Point*	sommets;
		
	public:
		Voxel(Point p, double r);
		void affiche();
		double getRayon();
		Point getSommet(int i);	
		
	
		//face avant haut droit bas gauche
		//Point p1, p2, p3, p4;
		//face arriere
		//Point p5, p6, p7, p8;
		
		/*
		float size;
		Voxel();
		Voxel(Point center, float size);
		Voxel(const Voxel& v);
		void subdiviseVoxel(int nb, Point*);*/


};

#endif
