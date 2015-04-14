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
#include <cmath>
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
int nbRegion = 0;
std::vector<Triangle>* listeRegion = new std::vector<Triangle>[256];
std::vector<Triangle> listeTriangle;

int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP8");

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
	normaleFace1.normalize();
	Vector normaleFace2 = normaleFace(t2);
	normaleFace2.normalize();
	
	double cos = normaleFace1.scalar(normaleFace2);
	
	if ( std::isnan(180*acos(cos)/M_PI)){
		return 0;
	}else{
		return ( 180*acos(cos)/M_PI);
	}
		
	

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

bool voisin(Triangle t, Triangle tPrim){

	int nbSommetCommun = 0;

	for(Point s : t.getSommets()){
		
		if( s.compare(tPrim.getSommetA()) || s.compare(tPrim.getSommetB()) || s.compare(tPrim.getSommetC())){
			nbSommetCommun++;
		}
	}
	
	if( nbSommetCommun == 2){
		return true;
	}else{
		return false;
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


void lectureFichierOFF(char* nomFichier,std::vector<Triangle> &listeTriangle){

	int nbSommet = 0;
	int nbTriangle = 0;
	int nbArete = 0;
	
	std::vector<Point> listePoint;
	
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

std::vector<Triangle> voisinsTriangle(std::vector<Triangle> listeTriangle, Triangle t){

	std::vector<Triangle> voisins;
	
	for(int i =0; i< listeTriangle.size(); i++){
			
		if( !listeTriangle.at(i).compareTriangle(t) && voisin(listeTriangle.at(i), t) ){
			voisins.push_back(listeTriangle.at(i));
		}
	}
	
	return voisins;

}

bool contient( std::vector<Triangle> listeTriangle, Triangle t){

	for(Triangle tPrim : listeTriangle){
		if( t.compareTriangle(tPrim)){
			return true;
		}
	}
	
	return false;
}

std::vector<Triangle> regionTriangle(Triangle t, std::vector<Triangle> listeTriangle){

	std::vector<Triangle> listeTrianglesRegion;
	std::vector<Triangle> trianglePossible;
	bool val = false;
	
	listeTrianglesRegion.push_back(t);
	trianglePossible = voisinsTriangle(listeTriangle, t);

	while (!trianglePossible.empty()){

		Triangle tPrim = trianglePossible.at(0);
		std::vector<Triangle> voisin = voisinsTriangle(listeTriangle, tPrim);
		val = false;
		
		for(Triangle v : voisin){
			if(contient(listeTrianglesRegion, v)){
				if ( angleDiedre( v, tPrim) < 20 ){
					listeTrianglesRegion.push_back(tPrim);
					val = true;
				}
			}
		}
		
		if(val){
			for(Triangle v : voisin){
				if(!contient(listeTrianglesRegion, v) && !contient(trianglePossible, v)){
					trianglePossible.push_back(v);
				}
			}
		
		}
		
		
		trianglePossible.erase (trianglePossible.begin());

	}
	
		
	return listeTrianglesRegion;
}

void segmentation(){

	while( !listeTriangle.empty()){
	//for(int i=0; i<8; i++){
		std::vector<Triangle> region = regionTriangle(listeTriangle.at(0),listeTriangle);
		
		listeRegion[nbRegion] = region;
		nbRegion++;
		
		std::vector<Triangle> nouvelleListe;

		for(Triangle t : listeTriangle){
			if( !contient(region, t)){
				
				nouvelleListe.push_back(t);
			}	
		}
		
		listeTriangle = nouvelleListe;	
	}	
}

void afficheRegion(){

	srand (time(NULL));
	
	for(int i=0; i<nbRegion; i++){
	
		double rouge = ((double)rand() / (double)(RAND_MAX));
		double vert  = ((double)rand() / (double)(RAND_MAX));
		double bleu  = ((double)rand() / (double)(RAND_MAX));
	
		for(Triangle t : listeRegion[i]){
			
			//glColor3f(1, 0, 0);
			glColor3f(rouge,vert,bleu);						
			glBegin(GL_TRIANGLES);
				glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
				glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
				glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
			glEnd();
		}
	
	}	
	

}

void render_scene(){

	char* nomFichier = (char*) "MeshSegmentation.off";
		
	if(nbRegion == 0){
	
		lectureFichierOFF(nomFichier, listeTriangle);
		segmentation();
	
	}
	
	affichage(listeTriangle);

	afficheRegion();
	
	
	
}




































