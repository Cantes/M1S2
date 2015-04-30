
#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include "Point.h"
#include "Triangle.h"

using namespace std;

class Voxel
{
	public:

		Voxel(int i, int j, int k, int val );//avec i,j,k les coordonnées du centre
        Point centre;
        int value;
        float dimXvox;
        float dimYvox;
        float dimZvox;

		//face avant haut droit bas gauche
		Point p0,p1, p2, p3, p4;
		//face arriere
		Point p5, p6, p7;

        //tableau des 6 voxels voisins
       vector<Point> getVoisins();
        int getValue();
        Triangle** getTriangle(int numFace);

        //================================================

		Point* sommets;
		float size;


        Point getCentre();
        float getLenght();

};

#endif
