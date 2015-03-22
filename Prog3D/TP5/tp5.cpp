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
void DrawCircle(float cx, float cy, float r, int num_segments); 
void afficheCylindre(int nbMeridien);
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y);


static float px = 1.0F;
static float py = 1.0F;
static float pz = 1.0F;
static float angle = 0;

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

bool voxelAppartientSphere(Voxel voxel, Point centreSphere, double rayonSphere){

	for( int i = 0; i<8; i++ ){
		if( distance(centreSphere, voxel.getSommet(i)) > rayonSphere ){
			return false;
		}
	}
	
	return true;
}

bool voxelHorsSphere(Voxel voxel, Point centreSphere, double rayonSphere){

	for( int i = 0; i<8; i++ ){
		if( distance(centreSphere, voxel.getSommet(i)) < rayonSphere ){
			return false;
		}
	}
	
	return true;
}

std::vector<Voxel> voxelSphere(Point centreSphere,double rayonSphere, Point centreVoxel, double rayonVoxel, double resolution){
	
	std::vector<Voxel> listeVoxel;
	
	Voxel v(centreVoxel, rayonVoxel);
	
	if(voxelAppartientSphere(v, centreSphere, rayonSphere)){
		listeVoxel.push_back(v);
	}else if( rayonVoxel > resolution && !voxelHorsSphere(v,centreSphere,rayonSphere)){
		for(int i=0; i<8; i++){
			
			Point centreSubVoxel(	(v.getSommet(i).getX()+centreVoxel.getX())/2, 
						(v.getSommet(i).getY()+centreVoxel.getY())/2, 
						(v.getSommet(i).getZ()+centreVoxel.getZ())/2
					);
							
			Voxel voxel(centreSubVoxel, rayonVoxel/2);
					
			if(voxelAppartientSphere(voxel, centreSphere, rayonSphere)){
				listeVoxel.push_back(voxel);
			}else if (!voxelHorsSphere(voxel,centreSphere, rayonSphere)){
				std::vector<Voxel> listeTmp = voxelSphere(centreSphere, rayonSphere, centreSubVoxel, rayonVoxel/2, resolution);
					
				for(Voxel vox : listeTmp){
					listeVoxel.push_back(vox);
				}
			}						
		}
	}
	
	return  listeVoxel;
	
}

std::vector<Voxel> sphereVolumique(Point centre, double rayon, double resolution){

	DrawCircle(0,0,rayon,100);
	
	std::vector<Voxel> listeVoxel;
	
	Voxel v(centre, rayon);
	
	if( voxelAppartientSphere(v, centre, rayon)){
		listeVoxel.push_back(v);
	}else if ( v.getRayon() > resolution){
	
		for(int i=0; i<8; i++){
		
			Point centreSubVoxel( 	(v.getSommet(i).getX()+centre.getX())/2,
						(v.getSommet(i).getY()+centre.getY())/2, 
						(v.getSommet(i).getZ()+centre.getZ())/2
					);		
						
			Voxel voxel(centreSubVoxel, rayon/2);
			
			if(voxelAppartientSphere(voxel, centre, rayon)){
				listeVoxel.push_back(v);
			}else if (!voxelHorsSphere(voxel,centre, rayon)){
				std::vector<Voxel> listeTmp = voxelSphere(centre, rayon, centreSubVoxel, rayon/2, resolution);
				
				for(Voxel vox : listeTmp){
					listeVoxel.push_back(vox);
				}
			}
		}
	}
	
	return listeVoxel;
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

bool voxelAppartientCylindre(Point origine, Vector vecteur,double rayon, Voxel v){

	Point limite(origine.getX()+vecteur.getX(), origine.getY()+vecteur.getY(),origine.getZ()+vecteur.getZ());
	int distancePointProjete;
	int distanceOrigineProjete;

	for( int i = 0; i<8; i++ ){
		Point projete(v.getSommet(i).projectOnLine(origine,limite));
		distancePointProjete = sqrt( pow(v.getSommet(i).getX()-projete.getX(),2)
				           + pow(v.getSommet(i).getY()-projete.getY(),2) 
				           + pow(v.getSommet(i).getZ()-projete.getZ(),2) 
				   );

		distanceOrigineProjete = sqrt( pow(origine.getX()-projete.getX(),2)
				      	     + pow(origine.getY()-projete.getY(),2) 
				             + pow(origine.getZ()-projete.getZ(),2) 
				   );				   
				   
		if( distancePointProjete > rayon || projete.getY() < origine.getY() || projete.getY() > limite.getY()   ){
			return false;
		}

	}
	
	return true;
}

bool voxelHorsCylindre(Point origine, Vector vecteur,double rayon, Voxel v){

	Point limite(origine.getX()+vecteur.getX(), origine.getY()+vecteur.getY(),origine.getZ()+vecteur.getZ());
	int distancePointProjete;

	for( int i = 0; i<8; i++ ){
		Point projete(v.getSommet(i).projectOnLine(origine,limite));
		distancePointProjete = sqrt( pow(v.getSommet(i).getX()-projete.getX(),2)
				           + pow(v.getSommet(i).getY()-projete.getY(),2) 
				           + pow(v.getSommet(i).getZ()-projete.getZ(),2) 
				   );			   
	
		if( distancePointProjete <= rayon && projete.getY() >= origine.getY() && projete.getY() <= limite.getY()   ){
			return false;
		}

	}
	
	return true;
}


std::vector<Voxel> voxelCylindre(Point origineAxe, Vector axeVecteur, double rayon, Point centreVoxel, double rayonVoxel, double resolution){

	std::vector<Voxel> listeVoxel;
	Voxel v(centreVoxel, rayonVoxel);
	
	if(voxelAppartientCylindre(origineAxe,axeVecteur, rayon,v)){
		listeVoxel.push_back(v);
	}else if( rayonVoxel > resolution && !voxelHorsCylindre(origineAxe, axeVecteur,rayon,v)){

		for(int i=0; i<8; i++){
			
			Point centreSubVoxel(	(v.getSommet(i).getX()+centreVoxel.getX())/2, 
						(v.getSommet(i).getY()+centreVoxel.getY())/2, 
						(v.getSommet(i).getZ()+centreVoxel.getZ())/2
					);
							
			Voxel voxel(centreSubVoxel, rayonVoxel/2);
			
			if(voxelAppartientCylindre(origineAxe,axeVecteur, rayon,voxel)){
				listeVoxel.push_back(voxel);
			}else if (!voxelHorsCylindre(origineAxe, axeVecteur,rayon,voxel)){
				std::vector<Voxel> listeTmp;
				listeTmp = voxelCylindre(origineAxe, axeVecteur, rayon, centreSubVoxel, rayonVoxel/2, resolution);
				
				for(Voxel vox : listeTmp){
					listeVoxel.push_back(vox);
				}
			}						
		}
	}
	
	return listeVoxel;

}

std::vector<Voxel> cylindreVolumique(Point origineAxe, Vector axeVecteur, double rayon,double resolution){

	afficheCylindre(10);

	Point limite(origineAxe.getX()+axeVecteur.getX(), origineAxe.getY()+axeVecteur.getY(),origineAxe.getZ()+axeVecteur.getZ());
	int distanceLimite = sqrt( pow(limite.getX()-origineAxe.getX(),2) + pow(limite.getY()-origineAxe.getY(),2) + pow(limite.getZ()-origineAxe.getZ(),2) );
	Voxel v(origineAxe, distanceLimite);
	
	std::vector<Voxel> listeVoxel;

	if( voxelAppartientCylindre(origineAxe,axeVecteur, rayon,v)){
		listeVoxel.push_back(v);
	}else if ( v.getRayon() > resolution){
	
		for(int i=0; i<8; i++){
		
			Point centreSubVoxel( 	(v.getSommet(i).getX()+origineAxe.getX())/2,
						(v.getSommet(i).getY()+origineAxe.getY())/2, 
						(v.getSommet(i).getZ()+origineAxe.getZ())/2
					);				
						
			Voxel voxel(centreSubVoxel, distanceLimite/2);
			
			if(voxelAppartientCylindre(origineAxe,axeVecteur, rayon,voxel)){
				listeVoxel.push_back(voxel);
			}else if (!voxelHorsCylindre(origineAxe,axeVecteur, rayon,voxel)){
				std::vector<Voxel> listeTmp;
				listeTmp = voxelCylindre(origineAxe, axeVecteur, rayon, centreSubVoxel, distanceLimite/2, resolution);
				
				for(Voxel vox : listeTmp){
					listeVoxel.push_back(vox);
				}
			}
		}
	}
	
	return listeVoxel;
}

void afficheCylindre(int nbMeridien){

	int rayon = 20;
	int hauteur = 30;
	double angle;
	Point* tableau = new Point[2*nbMeridien];
	
	for(int i=0; i<nbMeridien; i++){
		
		angle = 2*M_PI * i / nbMeridien;
		
		tableau[2*i] = Point(rayon*cos(angle),0, rayon*sin(angle));
		tableau[2*i+1] = Point(rayon*cos(angle),hauteur, rayon*sin(angle));
		
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

void affichage(std::vector<Voxel> listeVoxel){

	for(Voxel v : listeVoxel){
		afficheVoxel(v);
	}
}

void unionSphereCylindre(std::vector<Voxel> voxelSphere, std::vector<Voxel> voxelCylindre ){

	
	for(Voxel v : voxelSphere){
		afficheVoxel(v);
	}
	
	
	for(Voxel v : voxelCylindre){
		afficheVoxel(v);
	}

}


std::vector<Voxel> soustractionVoxelCylindre(Point origineAxe, Vector axeVecteur, double rayon, Point centreVoxel, double rayonVoxel, double resolution){

	std::vector<Voxel> listeVoxel;
	Voxel v(centreVoxel, rayonVoxel);
	
	if(voxelHorsCylindre(origineAxe,axeVecteur, rayon,v)){
		listeVoxel.push_back(v);
	}else if( rayonVoxel > resolution && !voxelAppartientCylindre(origineAxe, axeVecteur,rayon,v)){

		for(int i=0; i<8; i++){
			
			Point centreSubVoxel(	(v.getSommet(i).getX()+centreVoxel.getX())/2, 
						(v.getSommet(i).getY()+centreVoxel.getY())/2, 
						(v.getSommet(i).getZ()+centreVoxel.getZ())/2
					);
							
			Voxel voxel(centreSubVoxel, rayonVoxel/2);
			
			if(voxelHorsCylindre(origineAxe,axeVecteur, rayon,voxel)){
				listeVoxel.push_back(voxel);
			}else if (!voxelAppartientCylindre(origineAxe, axeVecteur,rayon,voxel)){
				std::vector<Voxel> listeTmp;
				listeTmp = soustractionVoxelCylindre(origineAxe, axeVecteur, rayon, centreSubVoxel, rayonVoxel/2, resolution);
				
				for(Voxel vox : listeTmp){
					listeVoxel.push_back(vox);
				}
			}						
		}
	}
	
	return listeVoxel;

}

void soustractionSphereCylindre(Point centreSphere, double rayonSphere, Point origineCylindre, Vector axeCylindre, double rayonCylindre , double resolution){

	std::vector<Voxel> voxelSphere = sphereVolumique(centreSphere,rayonSphere,resolution);
	std::vector<Voxel> soustractionVoxel;
	
	for(Voxel vox : voxelSphere){
		if(voxelHorsCylindre(origineCylindre,axeCylindre, rayonCylindre,vox)){
			soustractionVoxel.push_back(vox);
			//afficheVoxel(vox);
		}else if (!voxelAppartientCylindre(origineCylindre,axeCylindre, rayonCylindre,vox)){
			std::vector<Voxel> listeTmp;
			
			listeTmp = soustractionVoxelCylindre(origineCylindre, axeCylindre, rayonCylindre, vox.getCentre(), vox.getRayon(), resolution);
			
			for(Voxel voxel : listeTmp){
				soustractionVoxel.push_back(voxel);
			}			
			
		}
	}
	
	for(Voxel vox : soustractionVoxel){
		afficheVoxel(vox);
	}

}

void intersectionSphereCylindre(Point centreSphere, double rayonSphere, Point origineCylindre, Vector axeCylindre, double rayonCylindre , double resolution){

	/*
	std::vector<Voxel> voxelSphere = sphereVolumique(centreSphere,rayonSphere,resolution);
	
	for(Voxel vox : voxelSphere){
		if(voxelAppartientCylindre(origineCylindre,axeCylindre, rayonCylindre,vox)){
			afficheVoxel(vox);
		}
	}*/
	
	std::vector<Voxel> voxelSphere = sphereVolumique(centreSphere,rayonSphere,resolution);
	std::vector<Voxel> intersectionVoxel;
	
	for(Voxel vox : voxelSphere){
		if(voxelAppartientCylindre(origineCylindre,axeCylindre, rayonCylindre,vox)){
			intersectionVoxel.push_back(vox);
		}else if (!voxelHorsCylindre(origineCylindre,axeCylindre, rayonCylindre,vox)){
		
			std::vector<Voxel> listeTmp;
			
			listeTmp = voxelCylindre(origineCylindre, axeCylindre, rayonCylindre, vox.getCentre(), vox.getRayon(), resolution);
			
			for(Voxel voxel : listeTmp){
				intersectionVoxel.push_back(voxel);
			}		
		}
	}
	
	
	for(Voxel vox : intersectionVoxel){
		afficheVoxel(vox);
	}


}

void render_scene(){

	Point centreSphere(0,0,0);
	Point centreCylindre(0,0,0);
	Vector vecteur(0,30,0);
	double rayon = 20;
	double resolution = 0.5;
	
	std::vector<Voxel> voxelSphere = sphereVolumique(centreSphere,20,0.5);
	
	//affichage(voxelSphere);
	
	std::vector<Voxel> voxelCylindre = cylindreVolumique(centreCylindre,vecteur,20,0.5);
	
	//soustractionSphereCylindre(centreSphere,rayon,centreCylindre,vecteur, rayon , resolution);
	
	//intersectionSphereCylindre(centreSphere,rayon,centreCylindre,vecteur, rayon , resolution);
	
	//affichage(voxelCylindre);
	
	unionSphereCylindre(voxelSphere, voxelCylindre);


}




































