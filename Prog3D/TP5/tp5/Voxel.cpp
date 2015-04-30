#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "Point.h"
#include "Voxel.h"
#include <GL/freeglut.h>

using namespace std;

Voxel::Voxel(){}

Voxel::Voxel(Point center, float lenght)
{
	float rayon = lenght / 2;
	size = lenght;
	centre = center;
	sommets = new Point[8];


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


Point Voxel::getCentre(){
    return centre;
}

float Voxel::getLenght(){
    return size;
}


void Voxel::drawVoxel(){


glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //Voxel voxel(center, lenght);
  /* GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, 0.25f};
            GLfloat Vert[] = {0.0f, 0.8f, 0.0f, 0.25f};
            GLfloat Bleu[] = {0.0f, 0.0f, 0.8f, 0.25f};

            GLfloat Rose[] = {0.8f, 0.0f, 0.8f, 0.25f};
            GLfloat Cyan[] = {0.0f, 0.8f, 0.8f, 0.25f};*/

        //    GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.25f};

  glBegin(GL_POLYGON);

    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
    glVertex3f(p4.getX(), p4.getY(), p4.getZ());
  glEnd();


  glBegin(GL_POLYGON);
  //glColor3f(1.0, 0.0, 0.0);
    glVertex3f(p5.getX(), p5.getY(), p5.getZ());
    glVertex3f(p6.getX(), p6.getY(), p6.getZ());
    glVertex3f(p7.getX(), p7.getY(), p7.getZ());
    glVertex3f(p8.getX(), p8.getY(), p8.getZ());
  glEnd();

  glBegin(GL_POLYGON);
  //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p5.getX(), p5.getY(), p5.getZ());
    glVertex3f(p6.getX(), p6.getY(), p6.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glEnd();

  glBegin(GL_POLYGON);
 // glColor3f(0.0, 0.0, 1.0);
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glVertex3f(p6.getX(), p6.getY(), p6.getZ());
    glVertex3f(p7.getX(), p7.getY(), p7.getZ());
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(p7.getX(), p7.getY(), p7.getZ());
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
    glVertex3f(p4.getX(), p4.getY(), p4.getZ());
    glVertex3f(p8.getX(), p8.getY(), p8.getZ());
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p5.getX(), p5.getY(), p5.getZ());
    glVertex3f(p8.getX(), p8.getY(), p8.getZ());
    glVertex3f(p4.getX(), p4.getY(), p4.getZ());
  glEnd();
}

void Voxel::subdivise(){

    for( int i = 0; i <8; i++){
        double newX = (sommets[i].getX()+ centre.getX())/2;
        double newY = (sommets[i].getY()+ centre.getY())/2;
        double newZ = (sommets[i].getZ()+ centre.getZ())/2;
        Point newCtr(newX,newY,newZ);
        Voxel newV(newCtr,size/2);
    //    newV.drawVoxel();
        sousVoxels.push_back(newV);
    }
}

vector<Voxel> Voxel::getSousVoxels(){
return sousVoxels;
}
