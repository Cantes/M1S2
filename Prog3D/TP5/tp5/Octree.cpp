#include <iostream>
#include <vector>
#include <math.h>
#include "Point.h"
#include "Voxel.h"
#include "Octree.h"

using namespace std;

Octree::Octree(){
    center = Point(0,0,0);
    lenght = 1;

    for(int i = 0; i< 8; i++){
        m_children[i] = NULL;
    }
}

Octree::Octree(Point ctr, float longueur){

   lenght = longueur;
   center = ctr;

}



void Octree::subdivise(Point ctrSphere, float raySphere, double resolution){

    float cotePlusLong;
    Point sommetOc(center.getX() + rayon, center.getY() + rayon, center.getZ() - rayon);





}
