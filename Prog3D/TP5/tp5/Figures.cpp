#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "Point.h"
#include "Vector.h"
#include "Voxel.h"
#include "Figures.h"
#include <GL/freeglut.h>


Figures::Figures(){}


Figures::Figures(Point ctr, double ray, double reso){
    centre = ctr;
    rayon = ray;
    resolution = reso;
}
Figures::Figures(Vector axe,Point ctr, double ray, double reso){
    axeCylindre = axe;
    depart = ctr;
    rayon = ray;
    resolution = reso;
}


void Figures::drawSphereVolumic(){
    Voxel v( centre, 2*rayon);
    divide(v);
}

void Figures::divide (Voxel &v){
    GLfloat Rose[] = {0.8f, 0.0f, 0.8f, 0.25f};
  //  GLfloat Bleu[] = {0.0f, 0.0f, 0.8f, 0.05f};
    //  GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.01f};

   if(v.getLenght() > resolution){
            v.subdivise();
            vector<Voxel> enfants;
            enfants = v.getSousVoxels();
            for(int i =0; i < enfants.size();i++){
                float inter = interstecteSphere(enfants[i]);
                if(inter == 0)
                    divide(enfants[i]);
                else if (inter == 1){
                    glColor4fv(Rose);
                }
            }
         }
         else
            v.drawVoxel();
}

float Figures::interstecteSphere(Voxel &v){

    float intersect;
    double rayonVox = v.centre.distance(v.sommets[0]);
    double d = centre.distance(v.centre);

    if (d + rayonVox <= rayon) intersect = 1.0;
    else if (d - rayonVox >= rayon)intersect = -1.0;
    else intersect = 0;

    return intersect;
}

//======================cylindre================
void Figures::drawCylindreVolumic(){

        double sizeAxe = axeCylindre.Norme();//taille du voxel
        Point ctr = depart.multiply(axeCylindre,0.5);//ctr du voxel = ctr du vecteur
        Voxel v(ctr, sizeAxe +3);
       // v.drawVoxel();
        divideCylindre(v);
}

float Figures::intersectCylindre(Voxel &v){
    float res;
bool toutDehors = true;
bool toutDedans = true;

    for (int i =0; i < 8; i ++){
        Point som = v.sommets[i];
        Point projete = som.ProjectOnLine(axeCylindre,depart);
        double d = som.distance(projete);
        if (d <= rayon)toutDehors = false;
        if (d > rayon) toutDedans = false;
    }

    if (toutDedans) res = 1;//à l'intérieur
    if (toutDehors) res = -1;
    if ((!(toutDedans))&& (!(toutDehors))) res = 0;

  return res;
}
void Figures::divideCylindre(Voxel &v){
    GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.25f};

        if(v.getLenght()>resolution){
               v.subdivise();
            for (int j =0; j <v.getSousVoxels().size(); j++){
                 Voxel filsv = v.getSousVoxels()[j];

                 if(intersectCylindre(filsv) == 1){
                        glColor4fv(Jaune);

                 }
                 else if (intersectCylindre(filsv) == 0){
                        //printf("je rentre ici\n");
                        divideCylindre(filsv);
                 }
           }
       }
       else
        v.drawVoxel();
}

//======================operations sur figures======
void Figures::drawIntersection(Figures &cylindre){
    GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.25f};
    double sizeAxe = axeCylindre.Norme();//taille du voxel
    Point ctr = depart.multiply(axeCylindre,0.5);//ctr du voxel = ctr du vecteur
    Voxel v(ctr, sizeAxe +3);

    if(v.getLenght()>resolution){
       v.subdivise();
        for (int j =0; j <v.getSousVoxels().size(); j++){
            Voxel filsv = v.getSousVoxels()[j];
            if(interstecteSphere(filsv)==1){
                cylindre.divideCylindre(filsv);
            }
        }
    }
}

void Figures::divideCylOnlySphere(Voxel &v){
    GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.25f};
    if(v.getLenght()>resolution){
       v.subdivise();
       for (int j =0; j <v.getSousVoxels().size(); j++){
                 Voxel filsv = v.getSousVoxels()[j];

                 if(intersectCylindre(filsv) == 1){
                     if(interstecteSphere(filsv)== -1){
                        glColor4fv(Jaune);

                     }
                 }
                 else if (intersectCylindre(filsv) == 0){
                        //printf("je rentre ici\n");
                       divideCylOnlySphere(filsv);
                 }
           }
    }
    else
        v.drawVoxel();
}


void Figures::drawSoustractionSphere(Figures &cylindre){

    double sizeAxe = cylindre.axeCylindre.Norme();//taille du voxel
    Point ctr = depart.multiply(axeCylindre,0.5);//ctr du voxel = ctr du vecteur
    Voxel v(ctr, sizeAxe+3);
    divideCylOnlySphere(v);

}

void Figures::divideSphereOnlyCyl(Voxel &v){

  GLfloat Rose[] = {0.8f, 0.0f, 0.8f, 0.25f};

   if(v.getLenght() > resolution){
            v.subdivise();
             for (int j =0; j <v.getSousVoxels().size(); j++){
                 Voxel filsv = v.getSousVoxels()[j];
                float inter = interstecteSphere(filsv);

                 if (inter == 1){
                       if(intersectCylindre(filsv)== -1){
                            glColor4fv(Rose);

                       }
                 }
                 else if(inter == 0)
                       divideSphereOnlyCyl(filsv);
            }
    }
    else
         v.drawVoxel();
}



 void Figures::drawSoustractionCylindre(Figures &Sphere){
    rayon = Sphere.rayon;
    double sizeAxe = axeCylindre.Norme();//taille du voxel
    //Point ctr = depart.multiply(axeCylindre,0.5);//ctr du voxel = ctr du vecteur
    Voxel v(centre, sizeAxe+3);
        //v.drawVoxel();
    divideSphereOnlyCyl(v);

 }

void Figures::drawUnion(Figures &cylindre){
    drawSphereVolumic();
    cylindre.drawCylindreVolumic();
}

