#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include "Voxel.h"
#include "Figures.h"

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

int size = 10; // Taille du rep�re


// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

/*void *thread_1(void *arg) {
    usleep(100*1000);
    thread_1(NULL);
    return NULL;
}

void start_thread() {
	cout << "start_thread" << endl;
	pthread_t thread1;
    pthread_create(&thread1, NULL, thread_1, NULL);
}*/

GLint winWidth=WIDTH, winHeight=HEIGHT;
GLfloat eyeX=0.0, eyeY=0.0, eyeZ=2.0;
GLfloat theta=270.0, phi=180.0;
GLfloat upX=10.0, upY=10.0, upZ=10.0;
GLfloat r=2.0;

void eyePosition( void ) {
	eyeX = r * sin(theta*0.0174532) * sin(phi*0.0174532);
	eyeY = r * cos(theta*0.0174532);
	eyeZ = r * sin(theta*0.0174532) * cos(phi*0.0174532);
	GLfloat dt=1.0;
	GLfloat eyeXtemp = r * sin(theta*0.0174532-dt) * sin(phi*0.0174532);
	GLfloat eyeYtemp = r * cos(theta*0.0174532-dt);
	GLfloat eyeZtemp = r * sin(theta*0.0174532-dt) * cos(phi*0.0174532);

	upX=eyeXtemp-eyeX;
	upY=eyeYtemp-eyeY;
	upZ=eyeZtemp-eyeZ;

	glutPostRedisplay();
}

void onMouseMove(int x, int y) {
// Mouse point to angle conversion
   theta = (360.0/(double)winHeight)*(double)y*1.0; //3.0 rotations possible
   phi = (360.0/(double)winWidth)*(double)x*1.0;
// Restrict the angles within 0~360 deg (optional)
   if(theta > 360)theta = fmod((double)theta,360.0);
   if(phi > 360)phi = fmod((double)phi,360.0);
   eyePosition();
}

void drawVector(Point p, Vector v);

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



glutPassiveMotionFunc(&onMouseMove);
  // choix des proc�dures de callback pour
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);

glEnable(GL_BLEND);
  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 /*GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, 0.25f};
            GLfloat Vert[] = {0.0f, 0.8f, 0.0f, 0.25f};
            GLfloat Bleu[] = {0.0f, 0.0f, 0.8f, 0.25f};

            GLfloat Rose[] = {0.8f, 0.0f, 0.8f, 0.25f};
            GLfloat Cyan[] = {0.0f, 0.8f, 0.8f, 0.25f};

           GLfloat Jaune[] = {0.8f, 0.8f, 0.0f, 0.25f};*/

}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
    glPointSize(3);
//	start_thread();
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ,0,0,0,upX, upY, upZ);

  // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
  // � une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();
glutSwapBuffers();
  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
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
  glOrtho(-size, size, -size, size, -size*100, size*100);
	glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) {
  case KEY_ESC:
    exit(1);
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
//===========================EXERCICE 1==========================
/*
Voxel v = Voxel(Point(0, 0, 0), 10);
v.drawVoxel();
*/
//================================================================
//============================EXERCICE 2 - SPHERE ================

Point ctr(0,0,0);
double ray = 5;
double res = 0.3;
Figures sphere(ctr,ray,res);
//sphere.drawSphereVolumic();

//================================================================
//============================EXERCICE 2 - CYLINDRE ==============
Point dep(-5,0,0);
Vector v(12,0,0);
float resolution =0.4;
float rayon = 2;
Figures cylindre(v,dep,rayon,resolution);
//cylindre.drawCylindreVolumic();
//=================================================================
//=====================Exerice 3 ==================================
//sphere.drawIntersection(cylindre);
//sphere.drawSoustractionSphere(cylindre);
//cylindre.drawSoustractionCylindre(sphere);
sphere.drawUnion(cylindre);
 glFlush();
}


void drawVector(Point p, Vector v){
    glBegin(GL_LINES);
    glVertex3f(p.getX(), p.getY(), p.getZ());
    glVertex3f(p.getX()+v.getX(), p.getY()+v.getY(), p.getZ()+v.getZ());
    glEnd();
}






