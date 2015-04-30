#include <iostream>
#include <vector>
#include <math.h>
#include "Point.h"
#include "Voxel.h"
#include "Triangle.h"

using namespace std;

Voxel::Voxel(int i, int j, int k, int val ){

    centre = Point(i, j, k);
    value = val;
   /* dimXvox = abs((i - 0.5) - (i + 0.5)));
    dimYvox = abs((j - 0.5) - (j + 0.5)));
    dimZvox = abs((k - 0.5) - (k + 0.5)));*/

    //points de dessous :
    p0 = Point((i - 0.5), (j - 0.5), (k - 0.5));
    p1 = Point((i + 0.5), (j - 0.5), (k - 0.5));
    p2 = Point((i + 0.5), (j + 0.5), (k - 0.5));
    p3 = Point((i - 0.5), (j + 0.5), (k - 0.5));

    //points du dessus :
    p4 = Point((i - 0.5), (j - 0.5), (k + 0.5));
    p5 = Point((i + 0.5), (j - 0.5), (k + 0.5));
    p6 = Point((i + 0.5), (j + 0.5), (k + 0.5));
    p7 = Point((i - 0.5), (j + 0.5), (k + 0.5));

    //définition des voisins :



}

int Voxel::getValue(){
return value;
}

Point Voxel::getCentre(){
    return centre;
}

vector<Point> Voxel::getVoisins(){

     vector<Point> voisins;
    voisins.push_back(Point(centre.getX()+1,centre.getY(),centre.getZ()));
    voisins.push_back(Point(centre.getX()-1,centre.getY(),centre.getZ()));
    voisins.push_back(Point(centre.getX(),centre.getY()-1,centre.getZ()));
    voisins.push_back(Point(centre.getX(),centre.getY()+1,centre.getZ()));
    voisins.push_back(Point(centre.getX(),centre.getY(),centre.getZ()-1));
    voisins.push_back(Point(centre.getX(),centre.getY(),centre.getZ()+1));
 return voisins;
}


Triangle** Voxel::getTriangle(int numFace){
Triangle** tri = new Triangle*[2];

switch(numFace){

case 0 : //à gauche
    tri[0] = new Triangle(p0,p4,p3);
    tri[1] = new Triangle(p3,p4,p7);

    break;

case 1 : // à droite
    tri[0] = new Triangle(p1,p5,p2);
    tri[1] = new Triangle(p2,p5,p6);
    break;

case 2 : //en bas
    tri[0] = new Triangle(p0,p1,p2);
    tri[1] = new Triangle(p0,p2,p3);
    break;

case 3 : //en HAUT
    tri[0] = new Triangle(p4,p5,p6);
    tri[1] = new Triangle(p4,p6,p7);
    break;

case 4 : //derrière
    tri[0] = new Triangle(p3,p2,p6);
    tri[1] = new Triangle(p3,p6,p7);
    break;

case 5 : //DEVANT
    tri[0] = new Triangle(p0,p1,p5);
    tri[1] = new Triangle(p0,p5,p4);
    break;

}
    return tri;



}


