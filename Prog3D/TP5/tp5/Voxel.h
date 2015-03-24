#ifndef VOXEL_H
#define VOXEL_H

#include "Point.h"
#include <vector>

using namespace std;

class Voxel
{
	public:

        //attributs
        //========
		//face avant haut droit bas gauche
		Point p1, p2, p3, p4;
		//face arriere
		Point p5, p6, p7, p8;

		Point centre;
		Point* sommets;

		float size;

		Voxel();
		Voxel(Point center, float size);
		vector<Voxel> sousVoxels;

		//fonctions
		//==================

        void drawVoxel();
        void subdivise();
        Point getCentre();
        float getLenght();
        vector<Voxel> getSousVoxels();


};

#endif
