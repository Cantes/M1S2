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

#include "../TP1/Vector.h"
#include "../TP1/Point.h"

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


static float px = 1.0F;
static float py = 1.0F;
static float pz = 1.0F;
static float angle = M_PI;
static int mx;
static int my;
static int meridien = 8;
static int parallele = 8;


int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP4");

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
  
//	glEnable(GL_DEPTH_TEST); 	
  	glEnable(GL_LIGHTING); 
  	glEnable(GL_LIGHT0);
     
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

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);

  // toutes les transformations suivantes sŽappliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y){  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
  
  
  case 43: // Touche '+'
  	meridien++;
  	parallele++;
  	glutPostRedisplay();
  break;
  
  case 45: // Touche '-'
  	meridien--;
  	if(meridien < 1){
  		meridien = 1;
  	}
  	parallele--;
  	if(parallele < 1){
  		parallele = 1;
  	}
  	glutPostRedisplay();
  break;  
  
  case 105: // Touche 'i'
  	//px -= 0.1F*sin(angle);
  	angle -= 0.03F;
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
    
  case 115:
	py -= 0.03F;
	glutPostRedisplay();
    break;
  
  case 122:
	py += 0.03F;
	glutPostRedisplay();
    break;
    
   
     
  default:
    printf ("La touche %d n'est pas active.\n", key);
    break;
  }     
}


void afficheCylindre(int nbMeridien){

	int rayon = 10;
	int hauteur = 20;
	double angle;
	Point* tableau = new Point[2*nbMeridien];
	
	for(int i=0; i<nbMeridien; i++){
		
		angle = 2*M_PI * i / nbMeridien;
		
		tableau[2*i] = Point(rayon*cos(angle),rayon*sin(angle), -hauteur/2);
		tableau[2*i+1] = Point(rayon*cos(angle),rayon*sin(angle), hauteur/2);
		
		glColor3f(1, 0, 0);
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(rayon*cos(angle),rayon*sin(angle), -hauteur/2);
			glVertex3f(rayon*cos(angle),rayon*sin(angle), hauteur/2);
		glEnd();
		
	}
	
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	for(int i=0; i<=2*nbMeridien; i++){
		
			glVertex3f(tableau[(2*i)%(2*nbMeridien)].getX(),tableau[(2*i)%(2*nbMeridien)].getY(), tableau[(2*i)%(2*nbMeridien)].getZ());
			glVertex3f(tableau[(2*i+1)%(2*nbMeridien)].getX(),tableau[(2*i+1)%(2*nbMeridien)].getY(),tableau[(2*i+1)%(2*nbMeridien)].getZ());			
			glVertex3f(tableau[(2*i+3)%(2*nbMeridien)].getX(),tableau[(2*i+3)%(2*nbMeridien)].getY(),tableau[(2*i+3)%(2*nbMeridien)].getZ());
			glVertex3f(tableau[(2*i+2)%(2*nbMeridien)].getX(),tableau[(2*i+2)%(2*nbMeridien)].getY(),tableau[(2*i+2)%(2*nbMeridien)].getZ());

		
	}
	glEnd();	
}


void afficheCone(int nbMeridien){

	Point sommet(0,0,20);
	int rayonBase = 10;
	int hauteur = 15;
	Point* tableau = new Point[nbMeridien];
	
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
		glVertex3f(sommet.getX(),sommet.getY(),sommet.getZ());
	glEnd();
	
	for(int i=0; i<nbMeridien; i++){
		angle = 2*M_PI * i / nbMeridien;
		tableau[i] = Point(rayonBase*cos(angle),rayonBase*sin(angle), -hauteur);
		glColor3f(0, 1, 0);
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(rayonBase*cos(angle),rayonBase*sin(angle), -hauteur);
		glEnd();
	}
	
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(sommet.getX(),sommet.getY(),sommet.getZ());
	for(int i=0; i<=nbMeridien; i++){				
		glVertex3f(tableau[i % nbMeridien].getX(),tableau[i % nbMeridien].getY(),tableau[i % nbMeridien].getZ());	
	}
	glEnd();	
	
}

void afficheSphere(){

	int rayon = 20;
	Point centre(0,0,0);
	double phi = 0;
	double teta;
	int nbPoint = 10;
	int tailleM = nbPoint*meridien;
	int tailleP = nbPoint*parallele;
	
	Point* tableauMeridien = new Point[tailleM];
	Point* tableauParallele = new Point[tailleP];
	
	glColor3f(0, 1, 0);
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(rayon*sin(0)*cos(0),
				rayon*sin(0)*sin(0), 
				rayon*cos(0));
	
	for(int j=0; j<=parallele; j++){
		glVertex3f(rayon*sin(M_PI * 1 / parallele)*cos(2*M_PI * (j%parallele) / parallele),
				rayon*sin(M_PI * 1 / meridien)*sin(2*M_PI * (j%parallele) / parallele), 
				rayon*cos(M_PI * 1 / meridien));
	}
	
	glEnd();
	
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(rayon*sin(M_PI)*cos(2*M_PI),
				rayon*sin(M_PI)*sin(2*M_PI), 
				rayon*cos(M_PI));
	
	for(int j=0; j<=parallele; j++){
		glVertex3f(rayon*sin(M_PI * (parallele - 1) / parallele)*cos(2*M_PI * (j%parallele) / parallele),
				rayon*sin(M_PI * (parallele - 1)  / meridien)*sin(2*M_PI * (j%parallele) / parallele), 
				rayon*cos(M_PI * (parallele - 1)  / meridien));
	}
	
	glEnd();
	
	for(int i=1; i<meridien-1; i++){
		for(int j=0; j<parallele; j++){
			glBegin(GL_QUADS);
					glVertex3f(rayon*sin(M_PI * i / parallele)*cos(2*M_PI * j / parallele),
							rayon*sin(M_PI * i / meridien)*sin(2*M_PI * j / parallele), 
							rayon*cos(M_PI * i / meridien));
								
					glVertex3f(rayon*sin(M_PI * i / meridien)*cos(2*M_PI * (j+1) / parallele),
							rayon*sin(M_PI * i / meridien)*sin(2*M_PI * (j+1) / parallele), 
							rayon*cos(M_PI * i / meridien));
								
								
					glVertex3f(rayon*sin(M_PI * (i+1) / meridien)*cos(2*M_PI * (j+1) / parallele),
							rayon*sin(M_PI * (i+1) / meridien)*sin(2*M_PI * (j+1) / parallele), 
							rayon*cos(M_PI * (i+1) / meridien));
							
					glVertex3f(rayon*sin(M_PI * (i+1) / meridien)*cos(2*M_PI * j / parallele),
							rayon*sin(M_PI * (i+1) / meridien)*sin(2*M_PI * j / parallele), 
							rayon*cos(M_PI * (i+1) / meridien));
			glEnd();
		}
	}
}

void cylindre(int nbMeridien){

	int rayon = 20;
	int hauteur = 10;
	double angle;
	Vector vecteur(0,1,0);
	Point origine(4,5,-3);
	Point* tableau = new Point[2*nbMeridien];
	
	glColor3f(1, 1, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
		glVertex3f(4,5,0);
	glEnd();
	
	for(int i=0; i<nbMeridien; i++){
		
		angle = 2*M_PI * i / nbMeridien;
		
		tableau[2*i] = Point(origine.getX()+rayon*cos(angle),origine.getY() + -hauteur/2, origine.getZ()+rayon*sin(angle));
		tableau[2*i+1] = Point(origine.getX()+rayon*cos(angle),origine.getY()+ hauteur/2,origine.getZ()+rayon*sin(angle));
		
		glColor3f(1, 0, 0);
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(origine.getX()+rayon*cos(angle),origine.getY() + -hauteur/2, origine.getZ()+rayon*sin(angle));
			glVertex3f(origine.getX()+rayon*cos(angle),origine.getY()+ hauteur/2,origine.getZ()+rayon*sin(angle));
		glEnd();
		
	}
	
	
	for(int i=0; i<nbMeridien; i++){
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(tableau[(2*i)%(2*nbMeridien)].getX(),tableau[(2*i)%(2*nbMeridien)].getY(), tableau[(2*i)%(2*nbMeridien)].getZ());
			glVertex3f(tableau[(2*i+2)%(2*nbMeridien)].getX(),tableau[(2*i+2)%(2*nbMeridien)].getY(),tableau[(2*i+2)%(2*nbMeridien)].getZ());			
			glVertex3f(tableau[(2*i+3)%(2*nbMeridien)].getX(),tableau[(2*i+3)%(2*nbMeridien)].getY(),tableau[(2*i+3)%(2*nbMeridien)].getZ());
			glVertex3f(tableau[(2*i+1)%(2*nbMeridien)].getX(),tableau[(2*i+1)%(2*nbMeridien)].getY(),tableau[(2*i+1)%(2*nbMeridien)].getZ());

		glEnd();
	}	

}


void render_scene(){

	
	//afficheCylindre(10);	
	
	//afficheCone(20);
	
	afficheSphere();
	
	//cylindre(20);

}









































