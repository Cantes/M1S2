#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <iostream>"
#include <vector>

using namespace std;

#include <GL/freeglut.h>

// D�finition de la taille de la fen�tre
#define WIDTH  480
#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
//augmenter/diminuer le nombre de meridien/parallele
#define KEY_PLUS 61
#define KEY_MOINS 45


//parem�tres camera :
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

// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
void GLinitPositionCamera();
GLvoid window_key(unsigned char key, int x, int y);


void facettisationCylindre(double rayon, double hauteur, int nbMeridien);
void drawSegment(const Point& p1, const Point& p2);
void drawCylinder(vector<Point> northPoints, vector<Point> southPoints);

void facettisationCone(float rayon, float hauteur, Point sommet, int nbMeridien);
void drawCone(Point sommet, vector<Point> basePoints);

void facettisationSphere(float rayon, int nbMeridien, int nbParallele);

int main(int argc, char **argv)
{
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carr�");

  // initialisation de OpenGL et de la sc�ne
  initGL();
  init_scene();

  // choix des proc�dures de callback pour
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
  // � une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
}

//fonction qui sert � initialiser la position de ma cam�ra
void GLinitPositionCamera(){
glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport � la fen�tre.

  glOrtho(minOrtho, maxOrtho, minOrtho, maxOrtho, minOrtho, maxOrtho);
    gluLookAt(eyeX,eyeY,eyeZ,objX,objY,objZ,upX,upY,upZ);
  // toutes les transformations suivantes s�appliquent au mod�le de vue
  glMatrixMode(GL_MODELVIEW);
}
// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport � la fen�tre.
  glOrtho(minOrtho, maxOrtho, minOrtho, maxOrtho, minOrtho, maxOrtho);
    gluLookAt(0,9.0,5.0,0.0,0.0,0.0,0.0,1.0,1.0);
  // toutes les transformations suivantes s�appliquent au mod�le de vue
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

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

 case 109://"m" pour faire une rotation � droite
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

 case 113://"q" pour faire un zoom arri�re
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

 case 107://"k" pour faire une rotation � gauche
    angleRotateHor -= 5;
    eyeX = eyeX * cos(angleRotateHor) + eyeZ * sin(angleRotateHor);
    eyeZ = (- eyeX) * sin(angleRotateHor) + eyeZ * cos(angleRotateHor);
    GLinitPositionCamera();
     glClear(GL_COLOR_BUFFER_BIT);
    render_scene();
    glFlush();
    break;

  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//D�finition de la couleur
 glColor3f(1.0, 1.0, 1.0);

//==================CYLINDRE=======================
/*glColor3f(0, 1, 0);
facettisationCylindre(10, 20, 50);
drawCylinder(northPoints, southPoints);*/
//================================================

//==================CONE==========================
 //glColor3f(0, 1, 0);
  /* Point sommet = Point(0, 0, 20);
  facettisationCone(15, 20, sommet, 10);
drawCone(sommet, southPoints);*/
//=============================================

//==================SPHERE====================
glColor3f(0, 1, 0);
facettisationSphere(20, nbMeridien, nbParallele);

 glFlush();
}


void facettisationCylindre(double rayon, double hauteur, int nbMeridien)
{
  for (int i = 0; i < nbMeridien; i++)
  {
    double tetha = 2 * M_PI * ((double) i / nbMeridien);
    southPoints.push_back(Point(rayon * cos(tetha), rayon * sin(tetha), -hauteur/2));
    northPoints.push_back(Point(rayon * cos(tetha), rayon * sin(tetha), hauteur/2));
  }
}

void drawSegment(const Point& p1, const Point& p2)
{
  glBegin(GL_LINES);
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glEnd();
}
void drawCylinder(vector<Point> northPoints, vector<Point> southPoints)
{
  glBegin(GL_POLYGON);
  glColor3f(0, 1, 0);
  for(int i = 0; i < northPoints.size(); i++)
  {
    glVertex3f(northPoints[i].getX(), northPoints[i].getY(), northPoints[i].getZ());
  }
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0, 0, 1);
  for(int i = 0; i < southPoints.size(); i++)
  {
    glVertex3f(southPoints[i].getX(), southPoints[i].getY(), southPoints[i].getZ());
  }
  glEnd();

  for(int i = 0; i < northPoints.size(); i++)
  {
    glColor3f(1, 0, 0);
    drawSegment(northPoints[i], southPoints[i]);
  }
}

void facettisationCone(float rayon, float hauteur, Point sommet, int nbMeridien)
{
  for (int i = 0; i < nbMeridien; i++)
  {
    double tetha = 2 * M_PI * ((double) i / nbMeridien);
    southPoints.push_back(Point(rayon * cos(tetha), rayon * sin(tetha), -hauteur/2));
  }
}

void drawCone(Point sommet, vector<Point> basePoints)
{
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0, 1, 0);
    glVertex3f(sommet.getX(), sommet.getY(), sommet.getZ());
    for(int i = 0; i < basePoints.size(); i++)
    {
      glVertex3f(basePoints[i].getX(), basePoints[i].getY(), basePoints[i].getZ());
    }
  glEnd();

  for(int j = 0; j < basePoints.size(); j++)
    {
        glColor3f(1, 0, 0);
        drawSegment(sommet,basePoints[j]);
    }

}

void facettisationSphere(float rayon, int nbMeridien, int nbParallele)
{
  for(int i = 0; i < nbMeridien; i++)
  {
    double tetha = 2 * M_PI * ((double) i / nbMeridien);
    glBegin(GL_LINE_STRIP);
    for(int j = 0; j <= nbParallele; j++)
    {
      double phy = M_PI * ((double) j / nbParallele);
      Point tmp = Point(rayon * sin(phy) * cos(tetha), rayon * sin(phy) * sin(tetha), rayon * cos(phy));
      glVertex3f(tmp.getX(), tmp.getY(), tmp.getZ());
    }
    glEnd();
  }

  for(int i = 0; i <= nbParallele; i++)
  {
    double phy = M_PI * ((double) i / nbParallele);
    glBegin(GL_LINE_STRIP);
    for(int j = 0; j <= nbMeridien; j++)
    {
      double tetha = 2 * M_PI * ((double) j / nbMeridien);
      Point tmp = Point(rayon * sin(phy) * cos(tetha), rayon * sin(phy) * sin(tetha), rayon * cos(phy));
      glVertex3f(tmp.getX(), tmp.getY(), tmp.getZ());
    }
    glEnd();
  }
}
