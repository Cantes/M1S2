#ifndef OCTREE_H
#define OCTREE_H

#include "Point.h"
#include <vector>
using namespace std;

class Octree
{

   public :

        //attributs
        float lenght;
        Point center;
        float rayon = lenght/2;
   /*AxisAlignedBox        m_bounds;
   std::vector<OctreeObject>    m_objects; */// You can use a (intrusive) linked list instead but I like vector because of its contiguous memory
        Octree* m_children[8];

        //constructeurs
        Octree();
        Octree(Point ctr, float longueur);

        //fonctions :
        void subdivise(Point ctrSphere, float raySphere, double resolution);



};


#endif
