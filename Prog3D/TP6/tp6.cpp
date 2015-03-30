///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../TP1/Vector.h"
#include "../TP1/Point.h"
#include "Arete.h"
#include "Triangle.h"


/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h>

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 0


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27



// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);
float* limiteEspace(std::vector<Point> listePoint);
void lectureFichierOFF(char* nomFichier, std::vector<Point> &listePoint, std::vector<Triangle> &listeTriangle, std::vector<Arete> &listeArete);


static float px = 0.0F;
static float py = 0.0F;
static float pz = 0.0F;
static float angle = M_PI;


float Xmin = -10;
float Xmax = 10;
float Ymin = -10;
float Ymax = 10;
float Zmin = -10;
float Zmax = 10;


char nomFichier [256] = "bunny.off";
//char nomFichier [256] = "triceratops.off";
//char nomFichier [256] = "buddha.off";


int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP6");

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
GLvoid initGL(){

	glClearColor(RED, GREEN, BLUE, ALPHA);
 
     
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene(){

}

// fonction de call-back pour l'affichage dans la fenêtre

GLvoid window_display(){

	
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  
  glPushMatrix();
  
  gluLookAt(px,py,pz,
            px+sin(angle),py,pz+cos(angle),
            0.0,1.0,0.0);
  /* Affichage de la scene                      */
  render_scene();
  glPopMatrix();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  //render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
  
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height){
  
  glViewport(0, 0, width, height);
  
 
  std::vector<Point> listePoint;
  std::vector<Triangle> listeTriangle;
  std::vector<Arete> listeArete;
  
  lectureFichierOFF(nomFichier,listePoint,listeTriangle,listeArete);
	
  float* extrem = limiteEspace(listePoint);
  
  Xmin = extrem[0];
  Xmax = extrem[1];
  Ymin = extrem[2];
  Ymax = extrem[3];
  Zmin = extrem[4];
  Zmax = extrem[5];
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
   
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(Xmin, Xmax, Ymin,Ymax, Zmin, Zmax);

  // toutes les transformations suivantes sŽappliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y){  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;

  
  case 105: // Touche 'i'
  	//px -= 0.1F*sin(angle);
	pz -= 0.1F*cos(angle);
	glutPostRedisplay();
  break;
  
  
  case 107: // Touche 'k'
  	//px += 0.1F*sin(angle);
	pz += 0.1F*cos(angle);
	glutPostRedisplay();
  break;
   
  case 112:   // Touche 'p' 
      glutFullScreen ( );
  break;
  
  case 100:  
  	angle -= 0.03F;
  	glutPostRedisplay();                
    break;
    
  case 113:
  	angle += 0.03F;
  	glutPostRedisplay();   
    break;  
    
  case 115: // Touche s
	py -= 0.03F;
	glutPostRedisplay();
    break;
  
  case 122: // Touche z
	py += 0.03F;
	glutPostRedisplay();
    break;
    
   
     
  default:
    printf ("La touche %d n'est pas active.\n", key);
    break;
  }     
}

void lectureFichierOFF(char* nomFichier, std::vector<Point> &listePoint, std::vector<Triangle> &listeTriangle, std::vector<Arete> &listeArete){

	int nbSommet = 0;
	int nbTriangle = 0;
	int nbArete = 0;
	
	ifstream fichier(nomFichier, ios::in);
	 
        if(fichier){
        	string ligne;
                getline(fichier, ligne);
       
       		fichier >> nbSommet >> nbTriangle >> nbArete;
       		
       		long double x;
       		long double y;
       		long double z;
       		
       		
       		for(int i=0; i < nbSommet; i++){
       			fichier >> x >> y >> z;
       			Point p(x,y,z);
       			listePoint.push_back(p);
       		}
       		
       		int trash;
       		
		for(int i=0; i < nbTriangle; i++){
       			fichier >> trash >> x >> y >> z;
       			Triangle t(listePoint.at(x), listePoint.at(y),listePoint.at(z));
       			listeTriangle.push_back(t);
       		}
       		       		
                fichier.close();
        }else{
        	std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        }
                
}

//long double* limiteEspace(std::vector<Point> listePoint){
float* limiteEspace(std::vector<Point> listePoint){

	// 0 : min X
	// 1 : max X
	// 2 : min y
	// 3 : max Y
	// 4 : min Z
	// 5 : max Z
	
	//long double* extremite = new long double[6];
	float* extremite = new float[6];
	
	extremite[0] = 9999;
	extremite[2] = 9999;
	extremite[4] = 9999;
	extremite[1] = 0;
	extremite[3] = 0;
	extremite[5] = 0;
		
	for(Point p : listePoint){
	
		if(p.getX() < extremite[0]){
			extremite[0] = p.getX();
		}
		
		if(p.getX() > extremite[1]){
			extremite[1] = p.getX();
		}
		
		if(p.getY() < extremite[2]){
			extremite[2] = p.getY();
		}
		
		if(p.getY() > extremite[3]){
			extremite[3] = p.getY();
		}
		
		
		if(p.getZ() < extremite[4]){
			extremite[4] = p.getZ();
		}
		
		if(p.getZ() > extremite[5]){
			extremite[5] = p.getZ();
		}	

	}
	
	/*
	for(int i=0; i<6; i++){
		extremite[i] = extremite[i] * 2;
	}*/
	
	
	return extremite;

}

void affichage(std::vector<Triangle> listeTriangle){

	for(Triangle t : listeTriangle){
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
			glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
			glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
			glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
		glEnd();
	}

}


void render_scene(){

	
	std::vector<Point> listePoint;
	std::vector<Triangle> listeTriangle;
	std::vector<Arete> listeArete;

	lectureFichierOFF(nomFichier,listePoint,listeTriangle,listeArete);
	
	affichage(listeTriangle);

}















































