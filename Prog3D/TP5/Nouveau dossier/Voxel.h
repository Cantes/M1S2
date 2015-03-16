#ifndef VOXEL_H
#define VOXEL_H

#include "Point.h"
#include <vector>

using namespace std;

class Voxel
{
	public:


		//face avant haut droit bas gauche
		Point p1, p2, p3, p4;
		//face arriere
		Point p5, p6, p7, p8;
		Point* sommets;
		float size;
		Voxel();
		Voxel(Point center, float size);
		Voxel(const Voxel& v);
		void subdiviseVoxel(int nb, Point*);


};

#endif
