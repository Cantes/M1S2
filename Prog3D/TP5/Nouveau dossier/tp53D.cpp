#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <iostream>"
#include <vector>
#include "Voxel.h"

using namespace std;

#include <GL/freeglut.h>

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
//augmenter/diminuer le nombre de meridien/parallele
#define KEY_PLUS 61
#define KEY_MOINS 45


//paremètres camera :
double width = 480;
double height = 480;
double eyeX = 0;
double eyeY = 0;
double eyeZ = 1;
double objX = 0;
double objY = 0;
double objZ = 0;
double upX = 0;
double upY = 1;
double upZ = 0;
double angleRotateVert = 0;
double angleRotateHor = 0;
double maxOrtho = 50;
double minOrtho = -50;
int nbParallele = 8;
int nbMeridien = 8;

vector<Point> northPoints;
vector<Point> southPoints;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
void GLinitPositionCamera();
GLvoid window_key(unsigned char key, int x, int y);

void drawVoxel(Point center, float size);

//drawSphereVolumic(Point centre, double rayon, double résolution);

int main(int argc, char **argv)
{
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
  initGL();
  init_scene();

  // choix des procédures de callback pour
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

//fonction qui sert à initialiser la position de ma caméra
void GLinitPositionCamera(){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
  
	glLoadIdentity();

	glOrtho(minOrtho, maxOrtho, minOrtho, maxOrtho, minOrtho, maxOrtho);
	
	gluLookAt(eyeX,eyeY,eyeZ,objX,objY,objZ,upX,upY,upZ);
	
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(minOrtho, maxOrtho, minOrtho, maxOrtho, minOrtho, maxOrtho);
    gluLookAt(0,9.0,5.0,0.0,0.0,0.0,0.0,1.0,1.0);
  // toutes les transformations suivantes s´appliquent au modèle de vue
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) {
  case KEY_ESC:
    exit(1);
    break;
  case 111://"o" pour faire une rotation vers le haut
    angleRotateVert += 5;
    eyeY = eyeY * cos(angleRotateVert) - eyeZ * sin(angleRotateVert);
    eyeZ = eyeY * sin(angleRotateVert) + eyeZ * cos(angleRotateVert);
    GLinitPositionCamera();
     glClear(GL_COLOR_BUFFER_BIT);
    render_scene();
    glFlush();
    break;

 case 108://"l" pour faire une rotation vers le bas
    angleRotateVert -= 5;
    eyeY = eyeY * cos(angleRotateVert) - eyeZ * sin(angleRotateVert);
    eyeZ = eyeY * sin(angleRotateVert) + eyeZ * cos(angleRotateVert);
    GLinitPositionCamera();
    glClear(GL_COLOR_BUFFER_BIT);
    render_scene();
    glFlush();
    break;

 case 109://"m" pour faire une rotation à droite
    angleRotateHor += 5;
    eyeX = eyeX * cos(angleRotateHor) + eyeZ * sin(angleRotateHor);
    eyeZ = (- eyeX) * sin(angleRotateHor) + eyeZ * cos(angleRotateHor);
    GLinitPositionCamera();
    glClear(GL_COLOR_BUFFER_BIT);
    render_scene();
    glFlush();

    break;

 /*case 97://"a" pour faire un zoom avant
    valOrtho--;
    GLinitPositionCamera();
    render_scene();
    break;

 case 113://"q" pour faire un zoom arrière
    valOrtho++;
    GLinitPositionCamera();
    render_scene();
    break;*/

case KEY_PLUS:
    nbParallele++;
    nbMeridien++;
    window_display();
    break;
  case KEY_MOINS:
    if(nbParallele > 4)
    {
      nbParallele--;
      nbMeridien--;
    }
    window_display();
    break;

 case 107://"k" pour faire une rotation à gauche
    angleRotateHor -= 5;
    eyeX = eyeX * cos(angleRotateHor) + eyeZ * sin(angleRotateHor);
    eyeZ = (- eyeX) * sin(angleRotateHor) + eyeZ * cos(angleRotateHor);
    GLinitPositionCamera();
     glClear(GL_COLOR_BUFFER_BIT);
    render_scene();
    glFlush();
    break;

  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
 glColor3f(1.0, 1.0, 1.0);
 Voxel v = Voxel(Point(0, 0, 0), 2);
drawVoxel(Point(0, 0, 0), 20);
//drawSphereVolumic(Point centre, double rayon, double résolution);

 glFlush();
}

void drawVoxel(Point center, float lenght){

  Voxel voxel(center, lenght);

  glBegin(GL_POLYGON);
    glVertex3f(voxel.p1.getX(), voxel.p1.getY(), voxel.p1.getZ());
    glVertex3f(voxel.p2.getX(), voxel.p2.getY(), voxel.p2.getZ());
    glVertex3f(voxel.p3.getX(), voxel.p3.getY(), voxel.p3.getZ());
    glVertex3f(voxel.p4.getX(), voxel.p4.getY(), voxel.p4.getZ());
  glEnd();


  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
    glVertex3f(voxel.p5.getX(), voxel.p5.getY(), voxel.p5.getZ());
    glVertex3f(voxel.p6.getX(), voxel.p6.getY(), voxel.p6.getZ());
    glVertex3f(voxel.p7.getX(), voxel.p7.getY(), voxel.p7.getZ());
    glVertex3f(voxel.p8.getX(), voxel.p8.getY(), voxel.p8.getZ());
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0, 1.0, 0.0);
    glVertex3f(voxel.p1.getX(), voxel.p1.getY(), voxel.p1.getZ());
    glVertex3f(voxel.p5.getX(), voxel.p5.getY(), voxel.p5.getZ());
    glVertex3f(voxel.p6.getX(), voxel.p6.getY(), voxel.p6.getZ());
    glVertex3f(voxel.p2.getX(), voxel.p2.getY(), voxel.p2.getZ());
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);
    glVertex3f(voxel.p2.getX(), voxel.p2.getY(), voxel.p2.getZ());
    glVertex3f(voxel.p6.getX(), voxel.p6.getY(), voxel.p6.getZ());
    glVertex3f(voxel.p7.getX(), voxel.p7.getY(), voxel.p7.getZ());
    glVertex3f(voxel.p3.getX(), voxel.p3.getY(), voxel.p3.getZ());
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(voxel.p7.getX(), voxel.p7.getY(), voxel.p7.getZ());
    glVertex3f(voxel.p3.getX(), voxel.p3.getY(), voxel.p3.getZ());
    glVertex3f(voxel.p4.getX(), voxel.p4.getY(), voxel.p4.getZ());
    glVertex3f(voxel.p8.getX(), voxel.p8.getY(), voxel.p8.getZ());
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(voxel.p1.getX(), voxel.p1.getY(), voxel.p1.getZ());
    glVertex3f(voxel.p5.getX(), voxel.p5.getY(), voxel.p5.getZ());
    glVertex3f(voxel.p8.getX(), voxel.p8.getY(), voxel.p8.getZ());
    glVertex3f(voxel.p4.getX(), voxel.p4.getY(), voxel.p4.getZ());
  glEnd();
}

Point getCenter (Point ctr, Point sommet){
    Vector v = ctr.createVector(sommet);
    //v.changeSizeVector(0.5);
    Point newCenter = ctr.multiply(v,0.5);
    return newCenter;
}
bool interstecteSphere(double rayonSphere, Voxel v){

return false;

}

void drawSphereVolumic(Point centre, double rayon, double resolution){
    double coteVox = 2*rayon;
    Voxel vox(centre, coteVox);
    for (int i = 0 ; i <8; i++){
        //on détermine les centres ds nvx voxels
       Point newCtr = getCenter(centre,vox.sommets[i]);
        //on cré les nvx vox
//        Voxel newVox(newCtr, coteVox/2);
    }
}
