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
#include "Voxel.h"

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

int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP5");

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
  	/*glEnable(GL_LIGHTING); 
  	glEnable(GL_LIGHT0);*/
     
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
  /*
  gluLookAt(px,py,pz,
            px+sin(angle),py,pz+cos(angle),
            0.0,1.0,0.0);*/
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
   
  case 105: // Touche 'i'
  	//px -= 0.1F*sin(angle);
	pz += 0.1F;
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

double distance(Point centreSphere , Point p){
	return sqrt(pow(p.getX()-centreSphere.getX(),2)+pow(p.getY()-centreSphere.getY(),2)+pow(p.getZ()-centreSphere.getZ(),2));
}

void afficheVoxel(Voxel voxel){

	glBegin(GL_POLYGON);
    		glVertex3f(voxel.getSommet(0).getX(), voxel.getSommet(0).getY(), voxel.getSommet(0).getZ());
   		glVertex3f(voxel.getSommet(1).getX(), voxel.getSommet(1).getY(), voxel.getSommet(1).getZ());
    		glVertex3f(voxel.getSommet(2).getX(), voxel.getSommet(2).getY(), voxel.getSommet(2).getZ());
    		glVertex3f(voxel.getSommet(3).getX(), voxel.getSommet(3).getY(), voxel.getSommet(3).getZ());
  	glEnd();

 	glBegin(GL_POLYGON);
  		glColor3f(1.0, 0.0, 0.0);
    		glVertex3f(voxel.getSommet(4).getX(), voxel.getSommet(4).getY(), voxel.getSommet(4).getZ());
    		glVertex3f(voxel.getSommet(5).getX(), voxel.getSommet(5).getY(), voxel.getSommet(5).getZ());
    		glVertex3f(voxel.getSommet(6).getX(), voxel.getSommet(6).getY(), voxel.getSommet(6).getZ());
    		glVertex3f(voxel.getSommet(7).getX(), voxel.getSommet(7).getY(), voxel.getSommet(7).getZ());
  	glEnd();

  	glBegin(GL_POLYGON);
  		glColor3f(0.0, 1.0, 0.0);
    		glVertex3f(voxel.getSommet(0).getX(), voxel.getSommet(0).getY(), voxel.getSommet(0).getZ());
    		glVertex3f(voxel.getSommet(4).getX(), voxel.getSommet(4).getY(), voxel.getSommet(4).getZ());
    		glVertex3f(voxel.getSommet(5).getX(), voxel.getSommet(5).getY(), voxel.getSommet(5).getZ());
    		glVertex3f(voxel.getSommet(1).getX(), voxel.getSommet(1).getY(), voxel.getSommet(1).getZ());
  		glEnd();

  	glBegin(GL_POLYGON);
  		glColor3f(0.0, 0.0, 1.0);
    		glVertex3f(voxel.getSommet(1).getX(), voxel.getSommet(1).getY(), voxel.getSommet(1).getZ());
    		glVertex3f(voxel.getSommet(5).getX(), voxel.getSommet(5).getY(), voxel.getSommet(5).getZ());
    		glVertex3f(voxel.getSommet(6).getX(), voxel.getSommet(6).getY(), voxel.getSommet(6).getZ());
    		glVertex3f(voxel.getSommet(2).getX(), voxel.getSommet(2).getY(), voxel.getSommet(2).getZ());
  	glEnd();

  	glBegin(GL_POLYGON);
    		glVertex3f(voxel.getSommet(6).getX(), voxel.getSommet(6).getY(), voxel.getSommet(6).getZ());
    		glVertex3f(voxel.getSommet(2).getX(), voxel.getSommet(2).getY(), voxel.getSommet(2).getZ());
    		glVertex3f(voxel.getSommet(3).getX(), voxel.getSommet(3).getY(), voxel.getSommet(3).getZ());
    		glVertex3f(voxel.getSommet(7).getX(), voxel.getSommet(7).getY(), voxel.getSommet(7).getZ());
  	glEnd();

  	glBegin(GL_POLYGON);
    		glVertex3f(voxel.getSommet(0).getX(), voxel.getSommet(0).getY(), voxel.getSommet(0).getZ());
    		glVertex3f(voxel.getSommet(4).getX(), voxel.getSommet(4).getY(), voxel.getSommet(4).getZ());
    		glVertex3f(voxel.getSommet(7).getX(), voxel.getSommet(7).getY(), voxel.getSommet(7).getZ());
    		glVertex3f(voxel.getSommet(3).getX(), voxel.getSommet(3).getY(), voxel.getSommet(3).getZ());
  	glEnd();
}

bool appartientSphere(){

	return false;
}

void afficheVoxelSphere(Point centreSphere,double rayonSphere, Point centreVoxel, double rayonVoxel, double resolution){
	
	Voxel v(centreVoxel, rayonVoxel);
	
	if( rayonVoxel > resolution){
		for(int i=0; i<8; i++){
			if( distance(centreSphere, v.getSommet(i)) > rayonSphere){
				Point centreSubVoxel(v.getSommet(i).getX()-centreVoxel.getX(), v.getSommet(i).getY()-centreVoxel.getY(), v.getSommet(i).getY()-centreVoxel.getX());
				afficheVoxelSphere(centreSphere, rayonSphere, centreSubVoxel, rayonVoxel/2, resolution);	
			}else{
				Point centreSubVoxel(v.getSommet(i).getX()-centreVoxel.getX(), v.getSommet(i).getY()-centreVoxel.getY(), v.getSommet(i).getY()-centreVoxel.getX());
				Voxel voxel(centreSubVoxel, rayonVoxel/2);
				afficheVoxel(voxel);
			}
		}	
	}else{
		for(int i=0; i<8; i++){
		
			if( distance(centreSphere, v.getSommet(i)) <= rayonSphere){
				Point centreSubVoxel( (v.getSommet(i).getX()-centreVoxel.getX())/2, (v.getSommet(i).getY()-centreVoxel.getY())/2, (v.getSommet(i).getY()-centreVoxel.getX())/2);
				Voxel voxel(centreSubVoxel, rayonVoxel/2);
				afficheVoxel(voxel);
			}
		}		
	}
}

void afficheSphereVolumique(Point centre, double rayon, double resolution){

	Voxel v(centre, rayon);
	
	if( v.getRayon() > resolution){
		for(int i=0; i<8; i++){
		
			if( distance(centre, v.getSommet(i)) > rayon){
				Point centreSubVoxel( (v.getSommet(i).getX()-centre.getX())/2, (v.getSommet(i).getY()-centre.getY())/2, (v.getSommet(i).getY()-centre.getX())/2);
				afficheVoxelSphere(centre, rayon, centreSubVoxel, rayon/2, resolution);	
			}else{
				Point centreSubVoxel( (v.getSommet(i).getX()-centre.getX())/2, (v.getSommet(i).getY()-centre.getY())/2, (v.getSommet(i).getY()-centre.getX())/2);
				Voxel voxel(centreSubVoxel, rayon/2);
				afficheVoxel(voxel);
			}
		}
	}else{
		for(int i=0; i<8; i++){
			if( distance(centre, v.getSommet(i)) < rayon){
				Point centreSubVoxel( (v.getSommet(i).getX()-centre.getX())/2, (v.getSommet(i).getY()-centre.getY())/2, (v.getSommet(i).getY()-centre.getX())/2);
				Voxel voxel(centreSubVoxel, rayon/2);
				afficheVoxel(voxel);
			}
		}
	}
}

void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta); 

		glVertex2f(x + cx, y + cy);

	} 
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta); 
		
		glVertex3f(0, y + cy,x + cx); 

	} 
	glEnd();  
}

void render_scene(){

	
	DrawCircle(0,0,30,100);
	Point centre(0,0,0);
	afficheSphereVolumique(centre,30,15);

}









































