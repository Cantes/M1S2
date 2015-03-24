#ifndef FIGURES_H
#define FIGURES_H

#include "Point.h"
#include <vector>
#include "Vector.h"

using namespace std;

class Figures {

public :

    //attributs
    Point centre;
    double rayon;
    double resolution;
    Vector axeCylindre;
    Point depart;

    //constructeurs
    Figures();
    Figures(Point centre, double rayon, double resolution);
    Figures(Vector axe,Point depart, double rayon, double resolution);
    //fonctions
    void drawSphereVolumic();
    void divide (Voxel &v);
    float interstecteSphere(Voxel &v);

    void drawCylindreVolumic();
    float intersectCylindre(Voxel &v);
    void divideCylindre(Voxel &v);

    void drawIntersection(Figures &Cylindre);
    void divideCylOnlySphere(Voxel &v);
    void drawSoustractionSphere(Figures &Cylindre);
    void divideSphereOnlyCyl(Voxel &v);
    void drawSoustractionCylindre(Figures &Sphere);
    void drawUnion(Figures &Cylindre);




};


#endif
