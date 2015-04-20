///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille Université, site d'Arles
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Rendu réaliste
// Auteur : Sébastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une scène composée d'un sol, de
// maisons et d'arbres. On placera des sources de lumière, on spécifiera les
// matériaux des différents objets et on utilisera un effet de brouillard.
// ----------------------------------------------------------------------------
// Compilation sous Windows :
//   g++ -Wall maison.cpp -o maison.exe -lglut32 -lglu32 -lopengl32 -L.
// Compilation sous Linux :
//   g++ -Wall maison.cpp -o maison.exe -lglut -lGLU -lGL -L.
// Compilation sous MacOS :
//   g++ -framework GLUT -framework OpenGL maison.cpp -o maison.exe
///////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
//#include "glut.h"
#include <GL/glut.h>
#define WIDTH   800										// Largeur de la fenêtre OpenGL
#define HEIGHT  600										// Hauteur de la fenêtre OpenGl
#define KEY_ESC 27										// Code ASCII de la touche Echap

float	xpos = 0, zpos = -50;							// Position de la caméra
int		angle_x = 45, angle_y = 45;						// Orientation de la caméra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris
float posX = 0.0f;
float posY = 10.0f;
float posZ = 10.0f;

//*****************************************************************
//* A FAIRE :
//* Déclarer des tableaux contenant les caractéristiques (Ambient,
//* diffus, spéculaire) pour différents matériaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//*
//* Par exemple, pour le matériau de sol:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};	// On utilise des valeurs faibles pour Ambient (sombre, car à l'ombre)
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};	// On utilise des valeurs plus élevées pour Diffuse (partie éclairée)
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};	// Plus ces valeurs seront élevées, et plus le matériau sera luisant
//*   GLfloat MatShininess_sol[1]={5.0f};					// Plus cette valeurs era élevée (max=128) et plus le reflet sera petit
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains paramètres d'OpenGL.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL(){

	glClearColor(0, 0, 0, 1);							// Couleur servant à effacer la fenêtre (noir)
    	glShadeModel(GL_SMOOTH);							// Modèle d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cachées
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)


	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. Créer la source de lumière 0 (GL_LIGHT0) en tant que source de
	//*    lumière directionnelle, en précisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur spéculaire
	//*
	//* 2. Activer la source de lumière 0.
	//*
	//* 3. Activer l'éclairage général
	//*****************************************************************
/*
	GLfloat Light0Dif[]  = {0.0f, 0.7f, 0.0f, 1.0f};
	GLfloat Light0Spec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat Light0Amb[]  = {0.0f, 0.5f, 0.0f, 1.0f};
	GLfloat direction[]  = {1.0f, 0.0f,0.0f, 0.0f};
	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,Light0Dif );
	glLightfv(GL_LIGHT0,GL_SPECULAR,Light0Spec );
	glLightfv(GL_LIGHT0,GL_AMBIENT,Light0Amb );
	glLightfv(GL_LIGHT0,GL_POSITION,direction );
	
	
	GLfloat Light1Dif[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light1Spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light1Amb[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat directionLight1[]  = {posX, posY, posZ, 1.0f};
	
	glLightfv(GL_LIGHT1,GL_DIFFUSE,Light1Dif );
	glLightfv(GL_LIGHT1,GL_SPECULAR,Light1Spec );
	glLightfv(GL_LIGHT1,GL_AMBIENT,Light1Amb );
	glLightfv(GL_LIGHT1,GL_POSITION,directionLight1 );
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f);
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);*/
	

}



///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour le sol (utiliser glMaterialfv() pour les paramètres
	//* ambiant, diffus, speculaire du matériau du sol).
	//*****************************************************************
	//glColor3f(0.0f,0.8f,0.0f);							// Couleur courante : vert
	
	GLfloat matSpecSol[] = {0.5f, 1.0f,  0.5f, 1.0f};
	GLfloat matAmbSol[]  = {0.2f, 0.2f, 0.0f, 1.0f};
	GLfloat matDifSol[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecSol);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifSol);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbSol);
	
	glBegin(GL_QUADS);									// Affichage d'un quadrilatère
		glVertex3d(-20, 0, -20);
		glVertex3d(-20, 0,  20);
		glVertex3d( 20, 0,  20);
		glVertex3d( 20, 0, -20);
	glEnd();
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une maison.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degrés) de la maison p/r à l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);    							// et une rotation

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour les murs (utiliser glMaterialfv() pour les paramètres
	//* ambiant, diffus, speculaire du matériau du mur).
	//*****************************************************************
	glColor3f(1.0f,1.0f,1.0f);

	GLfloat matSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat matAmb[]  = {0.2f, 0.2f, 0.0f, 1.0f};
	GLfloat matDif[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	
	// Mur de face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex3d(-4, 5, 5);
		glVertex3d(-4, 0, 5);
		glVertex3d( 4, 0, 5);
		glVertex3d( 4, 5, 5);
	glEnd();

	// Mur arrière
	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_QUADS);
		glVertex3d( 4, 5, -5);
		glVertex3d( 4, 0, -5);
		glVertex3d(-4, 0, -5);
		glVertex3d(-4, 5, -5);
	glEnd();

	// Mur gauche
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3d(-4, 5, -5);
		glVertex3d(-4, 0, -5);
		glVertex3d(-4, 0,  5);
		glVertex3d(-4, 5,  5);
	glEnd();

	// Mur droit
	glNormal3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3d(4, 5,  5);
		glVertex3d(4, 0,  5);
		glVertex3d(4, 0, -5);
		glVertex3d(4, 5, -5);
	glEnd();

	// Triangle avant
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3d( 0, 9, 5);
		glVertex3d(-4, 5, 5);
		glVertex3d( 4, 5, 5);
	glEnd();

	// Triangle arrière
	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3d( 0, 9, -5);
		glVertex3d( 4, 5, -5);
		glVertex3d(-4, 5, -5);
	glEnd();

//*****************************************************************
//* A FAIRE :
//* Remplacer le glColor3f() suivant par l'utilisation du matériau
//* crée pour le toit (utiliser glMaterialfv() pour les paramètres
//* ambiant, diffus, speculaire du matériau du toit).
//*****************************************************************
	//glColor3f(1.0f,0.0f,0.0f);			// Couleur courante : rouge
	
	GLfloat matSpecToit[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat matAmbToit[]  = {0.2f, 0.0f, 0.0f, 1.0f};
	GLfloat matDifToit[]  = {0.1f, 0.0f, 0.0f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecToit);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifToit);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbToit);

	// Toit versant droit
	glNormal3f(0.707107f,0.707107f,0.0f);
	glBegin(GL_QUADS);
		glVertex3d(0, 9,  5);
		glVertex3d(4, 5,  5);
		glVertex3d(4, 5, -5);
		glVertex3d(0, 9, -5);
	glEnd();

	// Toit versant gauche
	glNormal3f(-0.707107f,0.707107f,0.0f);
	glBegin(GL_QUADS);
		glVertex3d( 0, 9, -5);
		glVertex3d(-4, 5, -5);
		glVertex3d(-4, 5,  5);
		glVertex3d( 0, 9,  5);
	glEnd();


	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_arbre( float xp, float yp, float zp )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne l'arbre avec une translation
	glRotatef(-90, 1,0,0);

	GLfloat matSpecTronc[] = {0.5f, 0.35f, 0.05f};
	GLfloat matAmbTronc[]  = {0.2f, 0.2f, 0.0f, 1.0f};
	GLfloat matDifTronc[]  = {0.1f, 0.1f, 0.0f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecTronc);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifTronc);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbTronc);
	
	glutSolidCone(2, 4, 10, 10);
	
	
	glTranslatef(0, 0, 6);
	
	GLfloat matSpecFeuille[] = {0.0f,0.8f,0.0f, 1.0f};
	GLfloat matAmbFeuille[]  = {0.2f, 0.2f, 0.0f, 1.0f};
	GLfloat matDifFeuille[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecFeuille);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifFeuille);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbFeuille);
	glutSolidSphere(2.5,10,10);

	glPopMatrix();										// Restaure la matrice de vue
}

void afficheSphereLumiere(){

	GLfloat Light1Dif[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light1Spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light1Amb[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat directionLight1[]  = {posX, posY, posZ, 1.0f};
	
	glLightfv(GL_LIGHT1,GL_DIFFUSE,Light1Dif );
	glLightfv(GL_LIGHT1,GL_SPECULAR,Light1Spec );
	glLightfv(GL_LIGHT1,GL_AMBIENT,Light1Amb );
	glLightfv(GL_LIGHT1,GL_POSITION,directionLight1 );
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f);
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glPushMatrix();
		glTranslatef(posX,posY,posZ);
		glutSolidSphere(1,5,5);
	glPopMatrix(); 
	
						
}



///////////////////////////////////////////////////////////////////////////////
// Affiche les différents objets de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_scene(){

	afficheSphereLumiere();
	affiche_sol();								// On affiche le sol.
	
	//*****************************************************************
	//* A FAIRE :
	//* Afficher quelques maisons et quelques arbres.
	//*
	//* Par exemple, on affiche ici une maison en (0,0,0),
	//* tournée de 20° :
	//*****************************************************************
	affiche_maison( -10, 0, -10, 0 );
	affiche_maison( -10, 0, 10, 0 );
	affiche_maison( 10, 0, -10, 0 );
	affiche_maison( 10, 0, 10, 0 );

	affiche_arbre(0,0,0);
	affiche_arbre(18,0,-18);
	affiche_arbre(18,0,18);
	affiche_arbre(-18,0,-18);
	affiche_arbre(-18,0,18);



	glutSwapBuffers();							// Affiche la scène à l'écran (affichage en double buffer)
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// On initialise la matrice de vue avec la matrice identité.
	glLoadIdentity();

	// On applique une translation et une rotation à la scène pour simuler
	// un déplacement de caméra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Re-spécifier la position des sources de lumière avec glLightfv()
	//* pour qu'elles soient aussi affectées par la translation et la
	//* rotation qu'on vient d'appliquer à la scène.
	//*****************************************************************


	// On affiche la scène.
	affiche_scene();

	// On force OpenGL à afficher avant de passer à la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : fonction appelée lorsqu'on redimensionne la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    width, height (in) : nouvelles largeur et hauteur de la fenêtre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height){

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}


//----------------------------------------------------------------------------------




///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des événements clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key){
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;
		
			
		case 100 :
			posX++;
			glutPostRedisplay();
			break;
			
		case 113 :
			posX--;
			glutPostRedisplay();
			break;	
				
		case 122 :
			posZ--;
			glutPostRedisplay();
			break;	
			
		case 115 :
			posZ++;
			glutPostRedisplay();
			break;
			
		case 114 :
			posY++;
			glutPostRedisplay();
			break;
		
		case 102 :
			posY--;
			glutPostRedisplay();
			break;			
									
		default:
			printf ("La touche %d n'est pas active.\n", key);
			break;
	}
	
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	float speed = 1.0f;						// Vitesse de déplacement de la caméra

	switch (key)
	{
		case GLUT_KEY_UP:					// Flèche vers le haut : 
			zpos += speed;					// on déplace la caméra selon z-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_DOWN:					// Flèche vers le bas :
			zpos -= speed;					// on déplace la caméra selon z+
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_LEFT:					// Flèche vers la gauche :
			xpos += speed;					// on déplace la caméra selon x-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_RIGHT:				// Flèche vers la droite :
			xpos -= speed;					// on déplace la caméra selon x+
			glutPostRedisplay();			// et on demande le réaffichage.
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    button (in) : code du bouton utilisé.
//    state  (in) : état du bouton.
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des déplacements de la souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la caméra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le réaffichage
}





///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// Paramètres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de chaînes de caractères contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Initialisation de paramètres de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation de paramètres d'OpenGL
	initGL();

	// Déclaration des fonctions de call-back.
	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc(&callback_keyboard);
	glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
	glutMainLoop();

	// Code de retour
	return 1;
}
