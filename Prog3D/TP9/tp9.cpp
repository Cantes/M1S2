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
#include "Cellule.h"

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
int tailleCellule = 2;

int main(int argc, char **argv){
  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP9");

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

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);

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
	tailleCellule++;
  	glutPostRedisplay();
  break;
  
  case 45: // Touche '-'
  	tailleCellule--;
  	if(tailleCellule < 5){
  		tailleCellule = 5;
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

void fusionSommets(Point sommet1, Point sommet2, std::vector<Triangle> &listeTriangle){

	Point nouveauSommet( (sommet1.getX() + sommet2.getX())/2, (sommet1.getY() + sommet2.getY())/2,(sommet1.getZ() + sommet2.getZ())/2);  
		
	for(int i=0; i<listeTriangle.size(); i++){
	
		if( listeTriangle.at(i).getSommetA().compare(sommet1) || listeTriangle.at(i).getSommetA().compare(sommet2) ){
			listeTriangle.at(i).setSommetA(nouveauSommet);
		}
		
		if( listeTriangle.at(i).getSommetB().compare(sommet1) || listeTriangle.at(i).getSommetB().compare(sommet2) ){
			listeTriangle.at(i).setSommetB(nouveauSommet);
		}
		
		if( listeTriangle.at(i).getSommetC().compare(sommet1) || listeTriangle.at(i).getSommetC().compare(sommet2) ){
			listeTriangle.at(i).setSommetC(nouveauSommet);
		}	
	}
}

void raffinementTriangle( Triangle t, std::vector<Triangle> &listeTriangle){

	Point nouveauSommetAB( (t.getSommetA().getX() + t.getSommetB().getX())/2, 
			       (t.getSommetA().getY() + t.getSommetB().getY())/2,
			       (t.getSommetA().getZ() + t.getSommetB().getZ())/2);  
			       
	Point nouveauSommetAC( (t.getSommetA().getX() + t.getSommetC().getX())/2, 
			       (t.getSommetA().getY() + t.getSommetC().getY())/2,
			       (t.getSommetA().getZ() + t.getSommetC().getZ())/2);  
			       
	Point nouveauSommetBC( (t.getSommetB().getX() + t.getSommetC().getX())/2, 
			       (t.getSommetB().getY() + t.getSommetC().getY())/2,
			       (t.getSommetB().getZ() + t.getSommetC().getZ())/2); 
			       
	Triangle t1(t.getSommetA(), nouveauSommetAB, nouveauSommetAC);
	Triangle t2(t.getSommetB(), nouveauSommetAB, nouveauSommetBC);
	Triangle t3(t.getSommetC(), nouveauSommetAC, nouveauSommetBC);
	Triangle t4(nouveauSommetAB, nouveauSommetAC, nouveauSommetBC);	
	
	for(int i=0; i<listeTriangle.size(); i++){
	
		if(t.compareTriangle( listeTriangle.at(i))){
			
			listeTriangle.erase(listeTriangle.begin() + i);
		}
	
	}	
	
	listeTriangle.push_back(t1);  
	listeTriangle.push_back(t2);   
	listeTriangle.push_back(t3);   
	listeTriangle.push_back(t4);       
	 
}

void afficheGrille( std::vector<Cellule> listeCellule){

	for(Cellule c : listeCellule){
	
		glBegin(GL_LINE_STRIP);
                        glVertex3f(c.getSommetA().getX(),c.getSommetA().getY(),0);
                        glVertex3f(c.getSommetB().getX(),c.getSommetB().getY(),0);
                        glVertex3f(c.getSommetC().getX(),c.getSommetC().getY(),0);
                        glVertex3f(c.getSommetD().getX(),c.getSommetD().getY(),0);
                        glVertex3f(c.getSommetA().getX(),c.getSommetA().getY(),0);
                glEnd();

	}

}

void fusionSommets(std::vector<Point> &listeSommet, std::vector<Triangle> &listeTriangle){


	while( listeSommet.size() > 1){
	
		Point nouveauSommet( (listeSommet.at(0).getX() + listeSommet.at(1).getX())/2,
			             (listeSommet.at(0).getY() + listeSommet.at(1).getY())/2,
			             (listeSommet.at(0).getZ() + listeSommet.at(1).getZ())/2 
			           );
			           
		for(int i=0; i<listeTriangle.size(); i++){
	
			if( listeTriangle.at(i).getSommetA().compare(listeSommet.at(0)) || listeTriangle.at(i).getSommetA().compare(listeSommet.at(1)) ){
				listeTriangle.at(i).setSommetA(nouveauSommet);
			}
		
			if( listeTriangle.at(i).getSommetB().compare(listeSommet.at(0)) || listeTriangle.at(i).getSommetB().compare(listeSommet.at(1)) ){
				listeTriangle.at(i).setSommetB(nouveauSommet);
			}
		
			if( listeTriangle.at(i).getSommetC().compare(listeSommet.at(0)) || listeTriangle.at(i).getSommetC().compare(listeSommet.at(1)) ){
				listeTriangle.at(i).setSommetC(nouveauSommet);
			}	
		}
		
		listeSommet.erase(listeSommet.begin());
		listeSommet.erase(listeSommet.begin());
		listeSommet.push_back(nouveauSommet);	  	           

	}
}

void simplificationCellule(std::vector<Triangle> &listeTriangle){

	std::vector<Cellule> listeCellule;
	
	for(int x=-30;x<=30;x=x+tailleCellule){
        
        	for(int y=-30;y<=30;y=y+tailleCellule){
        	
        		if( y+tailleCellule <=30 && x+tailleCellule <= 30){
			        Cellule c( Point(x,y,0), Point(x,y+tailleCellule,0),Point(x+tailleCellule,y+tailleCellule,0),Point(x+tailleCellule,y,0));
				listeCellule.push_back(c);       		
        		}

        	}	
        }
        
        afficheGrille(listeCellule);
        
        for(Cellule c : listeCellule){
       
       		//Cellule c = listeCellule.at(0);
        
        	std::vector<Point> sommetDansCellule;
        	
        	//std::cout << c.getXMin() << "," <<  c.getXMax() << "," << c.getYMin() << "," << c.getYMax() << std::endl;
        	
        	for(Triangle t : listeTriangle){
        	
        		if( c.appartientCellule(t.getSommetA())){
        			sommetDansCellule.push_back(t.getSommetA());	
        		}
        		
			if( c.appartientCellule(t.getSommetB())){
        			sommetDansCellule.push_back(t.getSommetB());	
        		}
        		
			if( c.appartientCellule(t.getSommetC())){
        			sommetDansCellule.push_back(t.getSommetC());	
        		}
        	}
        	
        	
        	fusionSommets(sommetDansCellule, listeTriangle);
        
        
        }
        
        
	
}

void render_scene(){

	//char* nomFichier = (char*) "cube.off";
	char* nomFichier = (char*) "MeshSegmentation.off";
	
	std::vector<Triangle> listeTriangle;
	
	lectureFichierOFF(nomFichier,listeTriangle);

	//fusionSommets( listeTriangle.at(0).getSommetA() , listeTriangle.at(8).getSommetB() , listeTriangle);
	
	//raffinementTriangle( listeTriangle.at(0),listeTriangle);
	
	simplificationCellule(listeTriangle);
		
	affichage(listeTriangle);
	
}




































