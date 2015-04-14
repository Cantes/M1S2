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
void DrawCircle(float cx, float cy, float r, int num_segments); 
void afficheCylindre(int nbMeridien);
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);


static float px = 1.0F;
static float py = 1.0F;
static float pz = 1.0F;
static float angle = M_PI;

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
  glutCreateWindow("TP7");

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
  
  	/*
	glEnable(GL_DEPTH_TEST); 	
  	glEnable(GL_LIGHTING); 
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
  glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

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
  	if(meridien < 4){
  		meridien = 4;
  	}
  	parallele--;
  	if(parallele < 4){
  		parallele = 4;
  	}
  	glutPostRedisplay();
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


std::vector<Triangle> triangulationCylindre(int rayon, int hauteur){

	double angle;
	Point* tableau = new Point[2*meridien];
	
	for(int i=0; i<meridien; i++){
		
		angle = 2*M_PI * i / meridien;
		
		tableau[2*i] = Point(rayon*cos(angle),rayon*sin(angle), -hauteur/2);
		tableau[2*i+1] = Point(rayon*cos(angle),rayon*sin(angle), hauteur/2);
				
	}
	
	std::vector<Triangle> triangleCylindre;
	for(int i=0; i<meridien; i++){
		Triangle t1(tableau[(2*i)%(2*meridien)],tableau[(2*(i+1) + 1)%(2*meridien)],tableau[(2*i+1)%(2*meridien)]);
		triangleCylindre.push_back(t1);
		
		Triangle t2(tableau[(2*i)%(2*meridien)],tableau[(2*(i+1))%(2*meridien)],tableau[(2*(i+1)+1)%(2*meridien)]);
		triangleCylindre.push_back(t2);
		
	}
	
	Point poleNord(0,0,hauteur/2 );
	Point poleSud(0,0, -hauteur/2 );
	
	
	for(int i=0; i<meridien; i++){
		Triangle t1(tableau[(2*i+1)%(2*meridien)],poleNord,tableau[(2*(i+1) +1 )%(2*meridien)]);
		triangleCylindre.push_back(t1);
				
	}
	
	for(int i=0; i<meridien; i++){
		Triangle t1(tableau[(2*i)%(2*meridien)],poleSud,tableau[(2*(i+1))%(2*meridien)]);
		triangleCylindre.push_back(t1);
				
	}
	
	

	
	return triangleCylindre;
}


std::vector<Triangle> triangulationSphere(Point centreSphere, int rayon){

	double phi = 0;
	double teta;
	int nbPoint = 10;
	int tailleM = nbPoint*meridien;
	int tailleP = nbPoint*parallele;
	
	std::vector<Triangle> listeTriangle;
		
	Point poleNord(rayon*sin(0)*cos(0), rayon*sin(0)*sin(0), rayon*cos(0));
	
	for(int j=0; j<=parallele; j++){
		
		Point p1(rayon*sin(M_PI * 1 / parallele)*cos(2*M_PI * (j%parallele) / parallele),
				rayon*sin(M_PI * 1 / meridien)*sin(2*M_PI * (j%parallele) / parallele), 
				rayon*cos(M_PI * 1 / meridien));
				
		Point p2(rayon*sin(M_PI * 1 / parallele)*cos(2*M_PI * ((j+1)%parallele) / parallele),
				rayon*sin(M_PI * 1 / meridien)*sin(2*M_PI * ((j+1)%parallele) / parallele), 
				rayon*cos(M_PI * 1 / meridien));
		
		Triangle t(poleNord,p1, p2);
		
		listeTriangle.push_back(t);
	}
	
	
	Point poleSud(rayon*sin(M_PI)*cos(2*M_PI), rayon*sin(M_PI)*sin(2*M_PI), rayon*cos(M_PI));
	
	for(int j=0; j<=parallele; j++){
		
		Point p1(rayon*sin(M_PI * (parallele - 1) / parallele)*cos(2*M_PI * (j%parallele) / parallele),
				rayon*sin(M_PI * (parallele - 1)  / meridien)*sin(2*M_PI * (j%parallele) / parallele), 
				rayon*cos(M_PI * (parallele - 1)  / meridien));
				
		Point p2(rayon*sin(M_PI * (parallele - 1) / parallele)*cos(2*M_PI * ((j+1)%parallele) / parallele),
				rayon*sin(M_PI * (parallele - 1)  / meridien)*sin(2*M_PI * ((j+1)%parallele) / parallele), 
				rayon*cos(M_PI * (parallele - 1)  / meridien));
		
		Triangle t(poleSud,p1, p2);
		
		listeTriangle.push_back(t);
	}
			
	for(int i=1; i<meridien-1; i++){
		for(int j=0; j<parallele; j++){
		
		
			Point p1(rayon*sin(M_PI * i / parallele)*cos(2*M_PI * j / parallele),
							rayon*sin(M_PI * i / meridien)*sin(2*M_PI * j / parallele), 
							rayon*cos(M_PI * i / meridien));
							
			Point p2(rayon*sin(M_PI * i / meridien)*cos(2*M_PI * (j+1) / parallele),
							rayon*sin(M_PI * i / meridien)*sin(2*M_PI * (j+1) / parallele), 
							rayon*cos(M_PI * i / meridien));
							
			Point p3(rayon*sin(M_PI * (i+1) / meridien)*cos(2*M_PI * (j+1) / parallele),
							rayon*sin(M_PI * (i+1) / meridien)*sin(2*M_PI * (j+1) / parallele), 
							rayon*cos(M_PI * (i+1) / meridien));
							
			Point p4(rayon*sin(M_PI * (i+1) / meridien)*cos(2*M_PI * j / parallele),
							rayon*sin(M_PI * (i+1) / meridien)*sin(2*M_PI * j / parallele), 
							rayon*cos(M_PI * (i+1) / meridien));				
		
			Triangle t1 (p1,p2,p3);
			
			listeTriangle.push_back(t1);
			
			Triangle t2(p1,p3,p4);
			
			listeTriangle.push_back(t2);
			
		}
	}
	
	return listeTriangle;
}

std::vector<Triangle> triangulationCube(int rayon){

	std::vector<Triangle> listeTriangle;
	
	
	Point p0(-rayon, rayon, - rayon); //en haut à gauche
	Point p1(rayon, rayon,  - rayon); //en haut à droite
	Point p2(rayon,  - rayon,  - rayon); //en bas à droite
	Point p3(- rayon, - rayon,  - rayon); //en bas à gauche
	
	Point p4( - rayon,  rayon,  rayon);
	Point p5( rayon,  rayon, rayon);
	Point p6( rayon,  - rayon, rayon);
	Point p7( - rayon, - rayon, rayon);
	
	
	listeTriangle.push_back(Triangle(p0,p1,p2));
	listeTriangle.push_back(Triangle(p0,p2,p3));
	
	listeTriangle.push_back(Triangle(p4,p5,p6));
	listeTriangle.push_back(Triangle(p4,p6,p7));
	
	listeTriangle.push_back(Triangle(p0,p4,p5));
	listeTriangle.push_back(Triangle(p0,p5,p1));
	
	listeTriangle.push_back(Triangle(p1,p5,p6));
	listeTriangle.push_back(Triangle(p1,p6,p2));
	
	listeTriangle.push_back(Triangle(p6,p2,p3));
	listeTriangle.push_back(Triangle(p6,p3,p7));
	
	listeTriangle.push_back(Triangle(p0,p4,p7));
	listeTriangle.push_back(Triangle(p0,p7,p3));


	return listeTriangle;

}

void affichage(std::vector<Triangle> listeTriangle){

	for(Triangle t : listeTriangle){
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
			glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
			glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
			glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
		glEnd();
	}
}

Vector produitVectoriel(Vector v1, Vector v2){

	return v1.vetoriel(v2);

}

Vector normaleFace(Triangle t){

	return	produitVectoriel(
		Vector(t.getSommetB().getX()-t.getSommetA().getX(),t.getSommetB().getY()-t.getSommetA().getY(),t.getSommetB().getZ()-t.getSommetA().getZ()), 
		Vector(t.getSommetC().getX()-t.getSommetA().getX(),t.getSommetC().getY()-t.getSommetA().getY(),t.getSommetC().getZ()-t.getSommetA().getZ())
				);

}

Vector normaleSommet(std::vector<Triangle> triangles,Point p){

	std::vector<Triangle> listeTriangle; 
	
	for(Triangle t : triangles){
		if(t.getSommetA().compare(p) || t.getSommetC().compare(p) || t.getSommetC().compare(p) ){
			listeTriangle.push_back(t);
		}
	}
	
	Vector vecteur(0,0,0);
	
	for(Triangle t : listeTriangle){
	
		Vector vecteurTmp = normaleFace(t);
		
		vecteur.setX(vecteur.getX() + vecteurTmp.getX());
		vecteur.setY(vecteur.getY() + vecteurTmp.getY());
		vecteur.setZ(vecteur.getZ() + vecteurTmp.getZ());
			
	}
	
	vecteur.setX(vecteur.getX() / listeTriangle.size());
	vecteur.setY(vecteur.getY() / listeTriangle.size());
	vecteur.setZ(vecteur.getZ() / listeTriangle.size());

	vecteur.normalize();
	
	return vecteur;
}

void affichageGauss(std::vector<Triangle> listeTriangle){

	for(Triangle t : listeTriangle){
	
		Vector vecteurA = normaleSommet(listeTriangle, t.getSommetA());
		
		Vector vecteurB = normaleSommet(listeTriangle, t.getSommetB());
		
		Vector vecteurC = normaleSommet(listeTriangle, t.getSommetC());
		
		glPointSize(5);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
			glVertex3f(vecteurA.getX()*10,vecteurA.getY()*10,vecteurA.getZ()*10);
			glVertex3f(vecteurB.getX()*10,vecteurB.getY()*10,vecteurB.getZ()*10);
			glVertex3f(vecteurC.getX()*10,vecteurC.getY()*10,vecteurC.getZ()*10);
		glEnd();
	
	}
}

double angleDiedre(Triangle t1, Triangle t2){

	Vector normaleFace1 = normaleFace(t1);
	Vector normaleFace2 = normaleFace(t2);
	
	double cos = normaleFace1.scalar(normaleFace2);
		
	return ( 180*acos(cos)/M_PI);

}

void afficheNormale(std::vector<Triangle> listeTriangle){

	for(Triangle t : listeTriangle){
	
		Vector normale = normaleFace(t);
		
		normale.normalize();
		
		normale.setX( normale.getX() *5 );
		normale.setY( normale.getY() *5  );
		normale.setZ( normale.getZ() *5  );

		glColor3f(0, 1, 0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
			glVertex3f(t.getSommetA().getX() + normale.getX(),t.getSommetA().getY() + normale.getY(),t.getSommetA().getZ() + normale.getZ());
		glEnd();
		
	
	}
}

Triangle adjacent(std::vector<Triangle> listeTriangle, Triangle triangle, Point A, Point B){

	int nbSommetCommun;
	
	for(Triangle t : listeTriangle ){
	
		if(! t.compareTriangle(triangle)){
		
			nbSommetCommun = 0;
			
			for(Point p : t.getSommets() ){
			
				if( p.compare(A) || p.compare(B) ){
					
					nbSommetCommun++;
				}
			}
			
			if(nbSommetCommun == 2){
			
				return t;
			}		
		}
	}
}

int* voisinageTriangle(std::vector<Triangle> listeTriangle){

	int* voisinage = new int[3*listeTriangle.size()];
	
	for(int i = 0; i<3*listeTriangle.size(); i++){
		voisinage[i] = -1;
	}
	
	int indice = 0;
	
	for(int i =0; i< listeTriangle.size(); i++){
	
		indice = 0;
		for(int j =0; j< listeTriangle.size(); j++){
		
			if( !listeTriangle.at(i).compareTriangle(listeTriangle.at(j)) && voisin(listeTriangle.at(i), listeTriangle.at(j)) ){
				voisinage[3*i + indice] = j;
				indice++;
			}
		}
	}
	
	return voisinage;

}

Point* areteCommune(Triangle t, Triangle tPrim){

	Point* tab = new Point[2];
	int ind = 0;
	
	for(Point p : t.getSommets()){
	
		for(Point pPrim : tPrim.getSommets()){
		
			if(p.compare(pPrim)){
			
				tab[ind] = p;
				ind++;
			}
		}
	}
	
	return tab;

}


void aretesVives ( std::vector<Triangle> listeTriangle, double angle){

	for(Triangle t : listeTriangle){
	
		Triangle triangleAdjacent1 =  adjacent(listeTriangle, t, t.getSommetA(), t.getSommetB());
		Triangle triangleAdjacent2 =  adjacent(listeTriangle, t, t.getSommetA(), t.getSommetC());
		Triangle triangleAdjacent3 =  adjacent(listeTriangle, t, t.getSommetB(), t.getSommetC());
		
		//std::cout << angleDiedre(t,triangleAdjacent1 ) << "," << angleDiedre(t,triangleAdjacent2 ) << "," << angleDiedre(t,triangleAdjacent3 ) << std::endl;
		
		if( angleDiedre(t,triangleAdjacent1 ) >= angle ){
		
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
				glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
			glEnd();
		
		}else{
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
				glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
			glEnd();
		}
		
		if( angleDiedre(t,triangleAdjacent2 ) >= angle ){
		
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
				glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glEnd();
		
		}else{
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
				glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glEnd();
		}
		
		if( angleDiedre(t,triangleAdjacent3 ) >= angle ){
		
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
				glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glEnd();
		
		}else{
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_STRIP);
				glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
				glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glEnd();
		}	
	}
}


void render_scene(){

	int rayon = 10;
	int hauteur = 30;
	Point centre(0,0,0);
	std::vector<Triangle> listeTriangle;
	
	listeTriangle = triangulationCylindre(rayon, hauteur);
	//listeTriangle = triangulationSphere(centre, rayon);
	//listeTriangle = triangulationCube(rayon);
	
	//affichage(listeTriangle);
	
	//affichageGauss(listeTriangle);
	
	//afficheNormale(listeTriangle);
	
	aretesVives(listeTriangle, 90);
	

}




































