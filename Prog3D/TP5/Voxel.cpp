#include <iostream>
#include <vector>
#include <math.h>
#include "Voxel.h"

Voxel::Voxel(Point centre, double r)
{

	rayon = r;
	
	sommets = new Point[8];
	
	sommets[0] = Point(centre.getX() - rayon, centre.getY() + rayon, centre.getZ() - rayon);//en haut à gauche
	sommets[1] = Point(centre.getX() + rayon, centre.getY() + rayon, centre.getZ() - rayon);//en haut à droite
	sommets[2] = Point(centre.getX() + rayon, centre.getY() - rayon, centre.getZ() - rayon);//en bas à droite
	sommets[3] = Point(centre.getX() - rayon, centre.getY() - rayon, centre.getZ() - rayon);//en bas à gauche

    	//points de derriere
	sommets[4] = Point(centre.getX() - rayon, centre.getY() + rayon, centre.getZ() + rayon);
	sommets[5] = Point(centre.getX() + rayon, centre.getY() + rayon, centre.getZ() + rayon);
	sommets[6] = Point(centre.getX() + rayon, centre.getY() - rayon, centre.getZ() + rayon);
	sommets[7] = Point(centre.getX() - rayon, centre.getY() - rayon, centre.getZ() + rayon);
}

Point Voxel::getSommet(int i){
	return sommets[i];
}

double Voxel::getRayon(){
	return rayon;
}

/*
void Voxel::subdiviseVoxel(int nb, Point* v)
{

	float sizeSousVoxel = size / nb;
	int l = 0;
	for(int i = 0; i < nb; i++)
	{
		for (int j = 0; j < nb; ++j)
		{
			for (int k = 0; k < nb; ++k)
			{
				Point centre = Point((p1.getX() + sizeSousVoxel * i) + (sizeSousVoxel / 2),
					(p1.getY() - sizeSousVoxel * j) - (sizeSousVoxel / 2),
					(p1.getZ() + sizeSousVoxel * k) + (sizeSousVoxel / 2));
				v[l] = centre;
				l++;
			}
		}
	}
}*/


