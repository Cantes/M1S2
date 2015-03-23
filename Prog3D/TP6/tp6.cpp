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


#include <GL/glut.h>

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
//augmenter/diminuer le nombre de meridien/parallele
#define KEY_PLUS 61
#define KEY_MOINS 45


//paremètres camera :
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
float vitesse = 1.0f;
double angleRotateVert = 0;
double angleRotateHor = 0;
double minX = -50;
double maxX = 50;
double minY = -50;
double maxY = 50;
double minZ = -50;
double maxZ = 50;
int nbParallele = 8;
int nbMeridien = 8;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
void GLinitPositionCamera();
GLvoid window_key(unsigned char key, int x, int y);

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP6");
	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);
	glutMainLoop();

	return 1;
	
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL(){

	glClearColor(RED, GREEN, BLUE, ALPHA);
	
}

void init_scene(){

}


GLvoid window_display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	render_scene();
	glFlush();
	
}

void GLinitPositionCamera(){

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minX, maxX, minY, maxY, minZ, maxZ);
	gluLookAt(eyeX,eyeY,eyeZ,objX,objY,objZ,upX,upY,upZ);
	glMatrixMode(GL_MODELVIEW);
	
}

GLvoid window_reshape(GLsizei width, GLsizei height){

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minX, maxX, minY, maxY, minZ, maxZ);
	gluLookAt(0,9.0,5.0,0.0,0.0,0.0,0.0,1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	
}

GLvoid window_key(unsigned char key, int x, int y){

	switch (key) {

		case KEY_ESC:
			exit(1);
		break;
	   
		case 122:	//Touche z
			angleRotateVert += vitesse;
			eyeY = eyeY * cos(angleRotateVert) - eyeZ * sin(angleRotateVert);
			eyeZ = eyeY * sin(angleRotateVert) + eyeZ * cos(angleRotateVert);
			GLinitPositionCamera();
			glClear(GL_COLOR_BUFFER_BIT);
			render_scene();
			glFlush();
		break;

		case 115:	// Touche s 
			angleRotateVert -= vitesse;
			eyeY = eyeY * cos(angleRotateVert) - eyeZ * sin(angleRotateVert);
			eyeZ = eyeY * sin(angleRotateVert) + eyeZ * cos(angleRotateVert);
			GLinitPositionCamera();
			glClear(GL_COLOR_BUFFER_BIT);
			render_scene();
			glFlush();
		break;

		case 100:	//Touche d
			angleRotateHor += vitesse;
			eyeX = eyeX * cos(angleRotateHor) + eyeZ * sin(angleRotateHor);
			eyeZ = (- eyeX) * sin(angleRotateHor) + eyeZ * cos(angleRotateHor);
			GLinitPositionCamera();
			glClear(GL_COLOR_BUFFER_BIT);
			render_scene();
			glFlush();
		break;
	    
		case 113:	//Touche q
			angleRotateHor -= vitesse;
			eyeX = eyeX * cos(angleRotateHor) + eyeZ * sin(angleRotateHor);
			eyeZ = (- eyeX) * sin(angleRotateHor) + eyeZ * cos(angleRotateHor);
			GLinitPositionCamera();
			glClear(GL_COLOR_BUFFER_BIT);
			render_scene();
			glFlush();
		break;
	/*
	case 105:	//Touche i
		valOrtho--;
		GLinitPositionCamera();
		render_scene();
	break;

	case 107:	//Touche k
		valOrtho++;
		GLinitPositionCamera();
		render_scene();
	break;*/

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

long double* limiteEspace(std::vector<Point> listePoint){

	// 0 : min X
	// 1 : max X
	// 2 : min y
	// 3 : max Y
	// 4 : min Z
	// 5 : max Z
	
	long double* extremite = new long double[6];
	
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
	
	for(int i=0; i<6; i++){
		extremite[i] = extremite[i] * 2;
	}
	
	
	return extremite;

}

void affichage(std::vector<Triangle> listeTriangle){

	for(Triangle t : listeTriangle){
		glColor3f(1, 0, 0);
		glBegin(GL_TRIANGLES);
			glVertex3f(t.getSommetA().getX(),t.getSommetA().getY(),t.getSommetA().getZ());
			glVertex3f(t.getSommetB().getX(),t.getSommetB().getY(),t.getSommetB().getZ());
			glVertex3f(t.getSommetC().getX(),t.getSommetC().getY(),t.getSommetC().getZ());
		glEnd();
	}

}

void redim(long double* extremite){

	minX = extremite[0];
	maxX = extremite[1];
	minY = extremite[2];
	maxY = extremite[3];
	minZ = extremite[4];
	maxZ = extremite[5];
		
	GLinitPositionCamera();
	glClear(GL_COLOR_BUFFER_BIT);
	render_scene();
	glFlush();
	
}

void render_scene(){

	char nomFichier [256] = "bunny.off";
	std::vector<Point> listePoint;
	std::vector<Triangle> listeTriangle;
	std::vector<Arete> listeArete;
		
	lectureFichierOFF(nomFichier,listePoint,listeTriangle,listeArete);
	
	long double* extrem = limiteEspace(listePoint);
	
	if(minX != extrem[0] ){
		std::cout << minX << "," << extrem[0] << std::endl;
		redim(extrem);
	}
	
	glColor3f(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();
	



}






