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
void DrawCurve(Point* TabPointsOfCurve,long nbPoints);
Point* BezierCurveByBernstein(Point* TabControlPoint, long nbControl, long nbU);
void traceCylindre(Point* TabPointsOfCurve, Point a, Point b);
void surfaceReglee(Point* TabPointsOfCurve, Point* TabPointsOfCurve2);
Point* BezierSurfaceByCasteljau(Point* TabControlPointU, int nbControlPointU, double nbU, 
				Point* TabControlPointV, int nbControlPointV, double nbV) ;
Point* BezierCurveByCasteljau(Point* TabControlPoint, long nbControl, double nbU);
void afficheSurfaceBezier(Point* tab, int tailleU, int tailleV);
double polyB(int n, double u);
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);

float axeX = 5.0;
float axeY = 5.0;
float axeZ = 5.0;

int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP3");

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

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
  
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height){
  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
  glMatrixMode(GL_MODELVIEW);
  
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y){  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
  
  case 112:    
      glutFullScreen ( );
  break;
  
  case 100:
	gluLookAt ( 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	glutPostRedisplay();            
    break;
    
  case 113: 
    break;  
     
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }  
  
  
  
     
}

//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene(){

	glColor3f(1.0, 1.0, 1.0);

	Point* tableauU = new Point[4];
	Point* tableauV = new Point[4];
	int tailleU = 4;
	int tailleV = 4;
	int pointsCourbe = 10;
	
	Point P0(0,0,0);
	Point P1(1,0,0);
	Point P2(2,0,0);
	Point P3(3,0,0);
	
	tableauU[0] = P0;
	tableauU[1] = P1;
	tableauU[2] = P2;
	tableauU[3] = P3;

	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex3f(P0.getX(), P0.getY(),P0.getZ());
		glVertex3f(P1.getX(), P1.getY(), P1.getZ());
		glVertex3f(P2.getX(), P2.getY(), P2.getZ());
		glVertex3f(P3.getX(), P3.getY(), P3.getZ());
		
	glEnd();
	
	Point* tabU = new Point[pointsCourbe];
	
	tabU = BezierCurveByBernstein(tableauU,3,pointsCourbe);
	
	DrawCurve(tabU,pointsCourbe);
	
	P0 = Point(0,0,0);
	P1 = Point(0,1,0);
	P2 = Point(0,2,0);
	P3 = Point(0,3,0);

	tableauV[0] = P0;
	tableauV[1] = P1;
	tableauV[2] = P2;
	tableauV[3] = P3;
	
	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex3f(P0.getX(), P0.getY(),P0.getZ());
		glVertex3f(P1.getX(), P1.getY(), P1.getZ());
		glVertex3f(P2.getX(), P2.getY(), P2.getZ());
		glVertex3f(P3.getX(), P3.getY(), P3.getZ());
		
	glEnd();

	Point* tabV = new Point[pointsCourbe];
	
	tabV = BezierCurveByBernstein(tableauV,3,pointsCourbe);
	
	DrawCurve(tabV,pointsCourbe);
	
	Point* tab = new Point[pointsCourbe * pointsCourbe];
	int ind = 0;
	double nbU, nbV;
	for(int i=0; i<pointsCourbe; i++){
		nbU = (double) i/pointsCourbe;
		for(int j = 0; j<pointsCourbe; j++){
			nbV = (double) j/pointsCourbe;
			tab[ind] = *BezierSurfaceByCasteljau(tableauU,4, nbU,tableauV,4, nbV); 
			ind++;
		}	
	}
	
	afficheSurfaceBezier(tab, pointsCourbe*pointsCourbe, tailleV);

}


void afficheSurfaceBezier(Point* tab, int tailleU, int tailleV){

	glPointSize(5);
	/*
	glColor3f(1, 0, 0);
	for(int i =0; i<=tailleU; i++){
		glBegin(GL_LINE_STRIP);
			for(int j=0; j<=tailleV; j++){
				glVertex3f(tab[(i*5)+j].getX(),tab[(i*5)+j].getY(),tab[(i*5)+j].getZ());			
			}
		glEnd();
	}*/
	
	for(int i=0; i<=tailleU; i++){
		glBegin(GL_POINTS);
			glVertex3f(tab[i].getX(),tab[i].getY(),tab[i].getZ());			
		glEnd();
	}
	
/*
	glColor3f(0, 0, 1);
	for(int i =0; i<=tailleV; i++){
		glBegin(GL_LINE_STRIP);
			for(int j=0; j<=tailleU; j++){
				glVertex3f(tab[i+(5*j)].getX(),tab[i+(5*j)].getY(),tab[i+(5*j)].getZ());			
			}
		glEnd();
	}*/

}


void DrawCurve(Point* TabPointsOfCurve,long nbPoints){

	glPointSize(5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<= nbPoints; i++){		
			glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY(), TabPointsOfCurve[i].getZ());			
		}
	glEnd();
}



int facto(int n){

	if(n == 0){
		return 1;
	}else{
		return n * facto(n -1);
	}

}

double polyB(int n, int i,double u){
	
	double fact = facto(n)/(facto(i)*facto(n-i));
	
	return fact*pow(u,i)*pow((1-u),(n-i));
}


Point* BezierCurveByBernstein(Point* TabControlPoint, long nbControl, long nbU){

	Point* tab = new Point[nbU + 1];
	Point* save;
	double poly;
	
	for(int i=0; i <= nbU; i++){
		save = new Point(0,0,0);
		poly = 0;
		for(int j=0; j <= nbControl; j++){
			poly = polyB(nbControl, j,(double) i / nbU);
			save = new Point( save->getX() + TabControlPoint[j].getX()*poly,
					  save->getY() + TabControlPoint[j].getY()*poly,
					  save->getZ() + TabControlPoint[j].getZ()*poly
					  ); 
		}
		
		tab[i] = *save;
		free(save);
	}
	
	return tab;
}


void traceCylindre(Point* TabPointsOfCurve, Point a, Point b){
	int u = 40;
	int v = 5;
	
	Vector vecteur( (b.getX() - a.getX()), b.getY() - a.getY(), b.getZ() - a.getZ());
	
	glColor3f(0, 1, 0);
	for(int i =0; i<=u; i++){
		glBegin(GL_LINE_STRIP);
			for(int j=0; j<=v; j++){
				glVertex3f(TabPointsOfCurve[i].getX() + vecteur.getX() * (double) j/v, 
				TabPointsOfCurve[i].getY() + vecteur.getY() * (double) j/v ,0);			
			}
		glEnd();
	}

	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i =0; i<=u; i++){
		for(int j=0; j<=v; j++){
			glVertex3f(TabPointsOfCurve[i].getX() + vecteur.getX() * (double) j/v, TabPointsOfCurve[i].getY() + vecteur.getY() * (double) j/v ,0);
		}

	}
	glEnd();
	
	glColor3f(1, 0, 0);
	for(int j=0; j<=v; j++){
		glBegin(GL_LINE_STRIP);
			for(int i =0; i<=u; i++){
				glVertex3f(TabPointsOfCurve[i].getX() + vecteur.getX() * (double) j/v, 
				TabPointsOfCurve[i].getY() + vecteur.getY() * (double) j/v ,0);			
			}
		glEnd();	
	}
}


void surfaceReglee(Point* TabPointsOfCurve, Point* TabPointsOfCurve2){

	int u = 50;
	int v = 5;
	
	
	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i =0; i<=u; i++){
		Vector vecteur( TabPointsOfCurve2[i].getX() - TabPointsOfCurve[i].getX(), TabPointsOfCurve2[i].getY()  - TabPointsOfCurve[i].getY(), TabPointsOfCurve2[i].getZ()  - TabPointsOfCurve[i].getZ());
		for(int j=0; j<=v; j++){
			glVertex3f(TabPointsOfCurve[i].getX() + vecteur.getX() * (double) j/v, TabPointsOfCurve[i].getY() + vecteur.getY() * (double) j/v ,0);
		}

	}
	glEnd();
	
	glColor3f(0.5, 0.5, 0);
	glBegin(GL_LINES);
	for(int i =0; i<=u; i++){
		glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY() ,0);	
		glVertex3f(TabPointsOfCurve2[i].getX(), TabPointsOfCurve2[i].getY() ,0);	

	}
	glEnd();
	
	glColor3f(1, 0, 0);
	for(int j =0; j<=v; j++){
		glBegin(GL_LINE_STRIP);
		for(int i =0; i<=u; i++){
				Vector vecteur( TabPointsOfCurve2[i].getX() - TabPointsOfCurve[i].getX(), 
						TabPointsOfCurve2[i].getY()  - TabPointsOfCurve[i].getY(), 
						TabPointsOfCurve2[i].getZ()  - TabPointsOfCurve[i].getZ());
						
			glVertex3f(TabPointsOfCurve[i].getX() + vecteur.getX() * (double) j/v, TabPointsOfCurve[i].getY() + vecteur.getY() * (double) j/v ,0);	
		}
		glEnd();
	}	
}


Point* BezierCurveByCasteljau(Point* TabControlPoint, long nbControl, double nbU){

	if(nbControl == 1){
		return TabControlPoint;
	}
	
	Point* tab = new Point[nbControl-1];
	
	for(int i =0; i<nbControl-1; i++){
			tab[i] = *(new Point( TabControlPoint[i].getX() + ((TabControlPoint[i+1].getX() - TabControlPoint[i].getX()) * nbU),
		  	     	      TabControlPoint[i].getY() + ((TabControlPoint[i+1].getY() - TabControlPoint[i].getY()) * nbU),
		             	 0
		       	 ));

	}
		
	return BezierCurveByCasteljau(tab, nbControl-1, nbU);

}

Point* BezierSurfaceByCasteljau(Point* TabControlPointU, int nbControlPointU, double nbU, 
				Point* TabControlPointV, int nbControlPointV, double nbV){
					
	if(nbControlPointU == 1){
		return BezierCurveByCasteljau(TabControlPointV,nbControlPointV,nbV);
	}else if(nbControlPointV == 1){
		return BezierCurveByCasteljau(TabControlPointU,nbControlPointU,nbU);
	}

	Point* tabU = new Point[nbControlPointU-1];
	Point* tabV = new Point[nbControlPointV-1];
	
	for(int i=0; i<nbControlPointU-1;i++){
		Vector vecteurU( TabControlPointU[i+1].getX() - TabControlPointU[i].getX(), 
				 TabControlPointU[i+1].getY() - TabControlPointU[i].getY(), 
				 TabControlPointU[i+1].getZ() - TabControlPointU[i].getZ()); 
				
		Vector vecteurV( TabControlPointV[1].getX() - TabControlPointV[0].getX(), 
				 TabControlPointV[1].getY() - TabControlPointV[0].getY(), 
				 TabControlPointV[1].getZ() - TabControlPointV[0].getZ()); 
					 
		tabU[i] = *(new Point( TabControlPointU[i].getX() + vecteurU.getX() * nbU,
				      TabControlPointU[i].getY() + vecteurV.getY() * nbV,
					0));
	}
	
	for(int i=0; i<nbControlPointU-1;i++){
		Vector vecteurU( TabControlPointU[1].getX() - TabControlPointU[0].getX(), 
				 TabControlPointU[1].getY() - TabControlPointU[0].getY(), 
				 TabControlPointU[1].getZ() - TabControlPointU[0].getZ()); 
				
		Vector vecteurV( TabControlPointV[i+1].getX() - TabControlPointV[i].getX(), 
				 TabControlPointV[i+1].getY() - TabControlPointV[i].getY(), 
				 TabControlPointV[i+1].getZ() - TabControlPointV[i].getZ()); 
					 
		tabV[i] = *(new Point( TabControlPointV[i].getX() + vecteurU.getX() * nbU,
				      TabControlPointV[i].getY() + vecteurV.getY() * nbV,
					0));
	}
				

	return BezierSurfaceByCasteljau(tabU, nbControlPointU - 1, nbU, 
					tabV, nbControlPointV - 1, nbV);					

}

































