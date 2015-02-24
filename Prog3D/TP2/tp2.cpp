///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "../TP1/Vector.h"
#include "../TP1/Point.h"

/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h> 

// D�finition de la taille de la fen�tre
#define WIDTH  480
#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 0


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27


// Ent�tes de fonctions
void init_scene();
void render_scene();
void DrawCurve(Point* TabPointsOfCurve,long nbPoints);
Point* HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU);
Point* BezierCurveByBernstein(Point* TabControlPoint, long nbControl, long nbU);
double polyB(int n, double u);
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);



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

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport � la fen�tre.
  glOrtho(0, 5.0, 0, 5.0, 0, 5.0);

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y){  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
    
  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
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
		       	 
		       	 cout << tab[i].getX() << "," << tab[i].getY() << "," << tab[i].getZ() << endl;
	}
	
	cout << endl;
	
	return BezierCurveByCasteljau(tab, nbControl-1, nbU);

}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene(){
//D�finition de la couleur
	glColor3f(1.0, 1.0, 1.0);
	
	Point* tableau = new Point[4];
	
	/*
	
	
	


	
		

	
	*/
	
	int pointsCourbe = 10;
	/*
	Point P0(0,0,0);
	Point P1(2,0,0);*/
	Vector V0(1,1,0);
	Vector V1(1,-1,0);
	
	
	Point P0(1,1,0);
	Point P1(2,3,0);
	Point P2(4,2,0);
	Point P3(3,0,0);
	
	
	tableau[0] = P0;
	tableau[1] = P1;
	tableau[2] = P2;
	tableau[3] = P3;

	Point* tab = HermiteCubicCurve(P0,P1,V0,V1, pointsCourbe);
		
	//Point* tab = BezierCurveByBernstein(tableau,3,pointsCourbe);
	
	/*
	Point* tab = new Point[pointsCourbe];
	for(int i=0; i<=pointsCourbe; i++){
		tab[i] = *BezierCurveByCasteljau(tableau,4, (double) i/ pointsCourbe ); 
	}*/

	
	glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex3f(P0.getX(), P0.getY(),P0.getZ());
		glVertex3f(P1.getX(), P1.getY(), P1.getZ());
		glVertex3f(P2.getX(), P2.getY(), P2.getZ());
		glVertex3f(P3.getX(), P3.getY(), P3.getZ());
		
	glEnd();
	
	glColor3f(0, 1, 0);	
	DrawCurve(tab,pointsCourbe);

}


void DrawCurve(Point* TabPointsOfCurve,long nbPoints){

	glPointSize(5);
	
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<= nbPoints; i++){		
			glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY(), TabPointsOfCurve[i].getZ());			
		}
	glEnd();
}



Point* HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU){
	
	Point* tab = new Point[nbU];
	double f1 = 0;
	double f2 = 0;
	double f3 = 0;
	double f4 = 0;
	
	for(int i=0; i<nbU; i++){
		f1 = 2*pow((double) i/nbU,3) - 3*pow((double)i/nbU,2) + 1;	
		f2 = -2*pow((double)i/nbU,3) + 3*pow((double)i/nbU,2);
		f3 = pow((double)i/nbU,3) - 2*pow((double)i/nbU,2) + (double)i/nbU;
		f4 = pow((double)i/nbU,3) - pow((double)i/nbU,2);
		
		Point a = Point(f1*P0.getX() + f2*P1.getX() + f3*V0.getX() + f4*V1.getX(),
				f1*P0.getY() + f2*P1.getY() + f3*V0.getY() + f4*V1.getY(),
				f1*P0.getZ() + f2*P1.getZ() + f3*V0.getZ() + f4*V1.getZ()
			);
		
		tab[i] = a;
	}
	
	return tab;	
	
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

	Point* tab = new Point[nbU];
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
