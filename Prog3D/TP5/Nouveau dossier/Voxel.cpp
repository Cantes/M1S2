#include <iostream>
#include <vector>
#include <math.h>
#include "Point.h"
#include "Voxel.h"

using namespace std;

Voxel::Voxel(){}

Voxel::Voxel(Point center, float lenght)
{
	float rayon = lenght / 2;
	size = lenght;
	//point de devant
	p1 = Point(center.getX() - rayon, center.getY() + rayon, center.getZ() - rayon);//en haut à gauche
	p2 = Point(center.getX() + rayon, center.getY() + rayon, center.getZ() - rayon);//en haut à droite
	p3 = Point(center.getX() + rayon, center.getY() - rayon, center.getZ() - rayon);//en bas à droite
	p4 = Point(center.getX() - rayon, center.getY() - rayon, center.getZ() - rayon);//en bas à gauche

    //points de dérrière
	p5 = Point(center.getX() - rayon, center.getY() + rayon, center.getZ() + rayon);
	p6 = Point(center.getX() + rayon, center.getY() + rayon, center.getZ() + rayon);
	p7 = Point(center.getX() + rayon, center.getY() - rayon, center.getZ() + rayon);
	p8 = Point(center.getX() - rayon, center.getY() - rayon, center.getZ() + rayon);

	sommets[0] = p1;
    sommets[1] = p2;
    sommets[2] = p3;
    sommets[3] = p4;
    sommets[4] = p5;
    sommets[5] = p6;
    sommets[6] = p7;
    sommets[7] = p8;
}

Voxel::Voxel(const Voxel& v)
{
	p1 = v.p1;
	p2 = v.p2;
	p3 = v.p3;
	p4 = v.p4;
	p5 = v.p5;
	p6 = v.p6;
	p7 = v.p7;
	p8 = v.p8;
}

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
				Point center = Point((p1.getX() + sizeSousVoxel * i) + (sizeSousVoxel / 2),
					(p1.getY() - sizeSousVoxel * j) - (sizeSousVoxel / 2),
					(p1.getZ() + sizeSousVoxel * k) + (sizeSousVoxel / 2));
				v[l] = center;
				l++;
			}
		}
	}
}


