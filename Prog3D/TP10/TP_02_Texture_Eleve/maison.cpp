///////////////////////////////////////////////////////////////////////////////
// IUT de Provence, site d'Arles                                      2003-2004
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Rendu réaliste
// Auteur : Sébastien Thon
// ----------------------------------------------------------------------------
// Base du TP 2
// Programme permettant d'ajouter des textures à une scène composée d'un sol,
// de maisons et d'arbres.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include "tga.h"

#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif

#define KEY_ESC 27										// Code ASCII de la touche Echap

#define MAISON  1										// Code identificant la display list de la maison
#define ARBRE   2										// Code identificant la display list de l'arbre

int		SCREEN_WIDTH =640;								// Largeur de la fenêtre OpenGL
int		SCREEN_HEIGHT=480;								// Hauteur de la fenêtre OpenGl

float	xpos = 0, zpos = -50;							// Position de la caméra
int		angle_x = 0, angle_y = 0;						// Orientation de la caméra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris



// Paramètres de la source de lumière 0 (directionnelle)
GLfloat Light0Position[]= { 4.0f, 4.0f, 2.0f, 0.0f };
GLfloat Light0Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat Light0Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };

// Paramètres de la source de lumière 1 (ponctuelle)
GLfloat Light1Position[]= { 4.0f, 8.0f, 2.0f, 1.0f };
GLfloat Light1Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat Light1Diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat Light1Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };


// Paramètres du matériau utilisé pour les murs
GLfloat MatAmbient_mur[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat MatDiffuse_mur[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat MatSpecular_mur[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_mur[1]={5.0f};

// Paramètres du matériau utilisé pour les toits
GLfloat MatAmbient_toit[] = {0.5f, 0.0f, 0.0f, 1.0f};
GLfloat MatDiffuse_toit[] = {0.9f, 0.0f, 0.0f, 1.0f};
GLfloat MatSpecular_toit[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_toit[1]={50.0f};

// Paramètres du matériau utilisé pour le sol
GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};
GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};
GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_sol[1]={5.0f};

// Paramètres du matériau utilisé pour la sphère représentant une source de lumière
GLfloat MatAmbient_lumiere[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat MatDiffuse_lumiere[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat MatSpecular_lumiere[]= {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat MatShininess_lumiere[1]={150.0f};

// Paramètres du matériau utilisé pour les troncs d'arbre
GLfloat MatAmbient_tronc[] = {0.5f, 0.4f, 0.2f, 1.0f};
GLfloat MatDiffuse_tronc[] = {0.9f, 0.4f, 0.2f, 1.0f};
GLfloat MatSpecular_tronc[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_tronc[1]={5.0f};

// Paramètres du matériau utilisé pour les feuillages d'arbres
GLfloat MatAmbient_feuilles[] = {0.0f, 0.4f, 0.0f, 1.0f};
GLfloat MatDiffuse_feuilles[] = {0.0f, 0.7f, 0.0f, 1.0f};
GLfloat MatSpecular_feuilles[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_feuilles[1]={5.0f};

// Couleur du brouillard
GLfloat fogColor[4]= {0.6f, 0.6f, 0.7f, 0.0f};


//*****************************************************************
//* A FAIRE :
//* Déclarer une constante pour le nombre de textures (5)
//*****************************************************************


//*****************************************************************
//* A FAIRE :
//* Déclarer une constante pour chacune des textures :
//*    - mur
//*    - façade
//*    - toit
//*    - herbe
//* Ex:
//*   #define TEXT_MUR		0
//*****************************************************************


//*****************************************************************
//* A FAIRE :
//* Déclarer un tableau "textures" de GLuint ayant autant de cases
//* qu'il y a de textures (utiliser la constante déclarée plus haut)
//* Ce tableau servira à stocker les identificateurs donnés par la
//* fonction glGenTextures() correspondant à chaque texture.
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Chargement d'une image et définition de la texture correspondante.
//-----------------------------------------------------------------------------
// Paramètres :
//    nom    (in): nom du fichier TGA à charger.
//    numero (in): identificateur (contenu dans textures[]) de la texture à charger.
//    mipmap (in): booléen indiquant s on veut utiliser la texture en tant que
//                 mipmap (true) ou non (false).
// Retour :
//    true si la texture a été chargée, false sinon.
///////////////////////////////////////////////////////////////////////////////
bool charge_texture( char *nom, GLuint indice, bool mipmap )
{
//*****************************************************************
//* A FAIRE :
//*  - Charger une image avec la fonction load_tga().
//*  - Si load_tga() retourne NULL, alors quitter la fonction
//*    en retournant false.
//*  - Utiliser glBindTexture() pour en faire la texture courante,
//*    sur laquelle porteront les opérations suivantes.
//*  - Utiliser glTexEnvf() pour spécifier le mode de mélange.
//*  - Spécifier le mode de bouclage.
//*  - Pour charger l'image en mémoire vidéo, tester la valeur du
//*    booléen mipmap :
//*       + Si mipmap == false
//*           - gluBuild2DMipmaps()
//*           - Spécifier le mode de filtrage.
//*       + Si mipmap == true
//*           - glTexImage2D()
//*           - Spécifier le mode de filtrage.
//*  - Supprimer le tableau dynamique alloué par load_tga(),
//*    l'image ayant été recopiée en mémoire vidéo.
//*****************************************************************

	return true;
}



///////////////////////////////////////////////////////////////////////////////
// Chargement des textures.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    true si toutes les textures ont été chargées, false sinon.
///////////////////////////////////////////////////////////////////////////////
bool charge_textures()
{
//*****************************************************************
//* A FAIRE :
//*  - appeler glGenTextures() pour demander à OpenGL de remplir
//*    le tableau "textures" avec autant d'identificateurs qu'il y
//*    a de textures.
//*  - appeler charge_texture() pour chaque texture, en fournissant
//*    comme identificateur celui placé dans le tableau "textures",
//*    et comme nom de fichier :
//*      - mur.tga
//*      - facade.tga
//*      - toit.tga
//*      - herbe.tga
//*  - si l'un des appels à charge_texture() retourne false, alors
//*    quitter la fonction en retournant false.
//*****************************************************************

	return true;
}



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains paramètres d'OpenGL.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL()
{
	glClearColor(0.6f, 0.6f, 0.7f, 1.0f);				// Couleur servant à effacer la fenêtre (celle du brouillard)
    glShadeModel(GL_SMOOTH);							// Modèle d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cachées
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);	// Couleur ambiante de la source de lumière 0 (directionnelle)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);	// Couleur diffuse de la source de lumière 0
	glLightfv(GL_LIGHT0, GL_SPECULAR,Light0Specular);	// Couleur spéculaire de la source de lumière 0
	glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);	// Direction de la source de lumière 0
	glEnable(GL_LIGHT0);								// Activation de la source de lumière 0

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient);	// Couleur ambiante de la source de lumière 1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse);	// Couleur diffuse de la source de lumière 1
	glLightfv(GL_LIGHT1, GL_SPECULAR,Light1Specular);	// Couleur spéculaire de la source de lumière 1
	glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);	// Position de la source de lumière 1
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02);	// Atténuation de la source de lumière 1
	glEnable(GL_LIGHT1);								// Activation de la source de lumière 1

	glEnable(GL_LIGHTING);								// Activation de l'éclairage général

	glFogi(GL_FOG_MODE, GL_LINEAR);						// Mode d'atténuation du brouillard (linéaire)
	glFogfv(GL_FOG_COLOR, fogColor);					// Couleur du brouillard
	glFogf(GL_FOG_START, 20.0f);						// Distance à laquelle débute le brouillard
	glFogf(GL_FOG_END, 80.0f);							// Distance à laquelle le brouillard est maximal
	glEnable(GL_FOG);									// Activation du brouillard
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
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_sol);	// Matériau courant
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_sol);
	glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_sol);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_sol);

//*****************************************************************
//* A FAIRE :
//*  - Activer le mode d'utilisation de textures.
//*  - Déclarer la texture d'herbe comme texture courante avec 
//*    glBindTexture() en spécifiant l'identificateur de la
//*    texture :  textures[TXT_HERBE].
//*  - Associer à chaque point3D du quad suivant les coordonnées
//*    d'un point (s,t) dans la texture, en faisant précéder chaque
//*    appel à glVertex3d() par un glTexCoord2f().
//*****************************************************************

	glNormal3f( 0.0f, 1.0f, 0.0f);						// Normale du quadrilatère

	glBegin(GL_QUADS);									// Affichage d'un quadrilatère
		glVertex3d(-20, 0, -20);
		glVertex3d(-20, 0,  20);
		glVertex3d( 20, 0,  20);
		glVertex3d( 20, 0, -20);
	glEnd();

//*****************************************************************
//* A FAIRE :
//*  - Désactiver le mode d'utilisation de textures si la scène
//*    doit comporter des objets non-texturés.
//*****************************************************************
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
	glRotatef(yr, 0,1,0);								// et une rotation
	glCallList(MAISON);									// Appelle la display list de la maison
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
	glCallList(ARBRE);									// Appelle la display list de l'arbre
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une sphère à l'emplacement de la source de lumière ponctuelle.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_soleil()
{
	// Utilise le matériau crée pour cet objet
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,MatSpecular_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess_lumiere);

	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(Light1Position[0], Light1Position[1], Light1Position[2]);	// Positionne la sphère
	glutSolidSphere(0.5, 20, 20);						// Affiche une sphère
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche les différents objets de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_scene()
{
	affiche_soleil();
	affiche_sol();

	affiche_maison( -10,  0,  0, 10 );
	affiche_maison(  10,  0, -8, 80 );
	affiche_maison(   4,  0, 10, 30 );

	affiche_arbre( -9,  0,-12 );
	affiche_arbre( -11, 0, 11 );
	affiche_arbre(  12, 0,  2 );

	glutSwapBuffers();									// Affiche la scène (affichage en double buffer)
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

	// On re-spécifie la position des sources de lumière avec pour qu'elles
	// soient aussi affectées par la translation et la rotation qu'on vient
	// d'appliquer à la scène.
	glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);
	glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);

	// Affiche la scène.
	affiche_scene();

	// On force OpenGL à afficher avant de passer à la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : redimensionnement de la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    width, height (in) : nouvelles largeur et hauteur de la fenêtre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	SCREEN_WIDTH  = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



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
	float speed = 1.0f;						// Vitesse de déplacement de la source de lumière

	switch (key)
	{
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;

		case 56 :							// '8': on déplace la source de lumière 1
			Light1Position[2] -=speed;		// selon z-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case 50 :							// '2': on déplace la source de lumière 1
			Light1Position[2] +=speed;		// selon z+
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case 52 :							// '4': on déplace la source de lumière 1
			Light1Position[0] -=speed;		// selon x-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case 54 :							// '6': on déplace la source de lumière 1
			Light1Position[0] +=speed;		// selon x+
			glutPostRedisplay();			// et on demande le réaffichage.
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
// Construit une maison dans une display-list.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_maison()
{
	glNewList(MAISON, GL_COMPILE);

//*****************************************************************
//* A FAIRE :
//*  - Activer le mode d'utilisation de textures.
//*****************************************************************

		// On spécifie comme matériau courant celui correspondant au mur
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_mur);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_mur);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_mur);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_mur);

//*****************************************************************
//* A FAIRE :
//*  - Déclarer la texture de mur comme texture courante avec 
//*    glBindTexture() en spécifiant l'indice de la texture :
//*    textures[TXT_MUR].
//*  - Associer à chaque point3D des polygones suivants les
//*    coordonnées d'un point (s,t) dans la texture, en faisant
//*    précéder chaque appel à glVertex3d() par un glTexCoord2f().
//*****************************************************************

		// Mur de face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, 5);
			glVertex3d( 4, 0, 5);
			glVertex3d( 4, 5, 5);
			glVertex3d(-4, 5, 5);
		glEnd();

		// Mur arrière
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, -5);
			glVertex3d(-4, 5, -5);
			glVertex3d( 4, 5, -5);
			glVertex3d( 4, 0, -5);
		glEnd();

		// Mur droit
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3d(4, 0, -5);
			glVertex3d(4, 5, -5);
			glVertex3d(4, 5,  5);
			glVertex3d(4, 0,  5);
		glEnd();

		// Triangle avant
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3d(-4, 5,   5);
			glVertex3d( 4, 5,   5);
			glVertex3d( 0, 7.5, 5);
		glEnd();

		// Triangle arrière
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3d( 4, 5,   -5);
			glVertex3d(-4, 5,   -5);
			glVertex3d( 0, 7.5, -5);
		glEnd();

//*****************************************************************
//* A FAIRE :
//*  - Déclarer la texture de façade comme texture courante avec 
//*    glBindTexture() en spécifiant l'indice de la texture :
//*    textures[TXT_FACADE].
//*  - Associer à chaque point3D du quad suivant les
//*    coordonnées d'un point (s,t) dans la texture, en faisant
//*    précéder chaque appel à glVertex3d() par un glTexCoord2f().
//*****************************************************************

		// Mur gauche
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, -5);
			glVertex3d(-4, 0,  5);
			glVertex3d(-4, 5,  5);
			glVertex3d(-4, 5, -5);
		glEnd();


		// On spécifie comme matériau courant celui correspondant au toit
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_toit);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_toit);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_toit);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_toit);

//*****************************************************************
//* A FAIRE :
//*  - Déclarer la texture de toit comme texture courante avec 
//*    glBindTexture() en spécifiant l'indice de la texture :
//*    textures[TXT_TOIT].
//*  - Associer à chaque point3D des quads suivants les
//*    coordonnées d'un point (s,t) dans la texture, en faisant
//*    précéder chaque appel à glVertex3d() par un glTexCoord2f().
//*****************************************************************

		// Toit droit
		glNormal3f( 0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3d(0, 7.5, 5);
			glVertex3d(4, 5, 5);
			glVertex3d(4, 5, -5);
			glVertex3d(0, 7.5, -5);
		glEnd();

		// Toit gauche
		glNormal3f( -0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3d(0, 7.5, 5);
			glVertex3d(0, 7.5, -5);
			glVertex3d(-4, 5, -5);
			glVertex3d(-4, 5, 5);
		glEnd();

//*****************************************************************
//* A FAIRE :
//*  - Désactiver le mode d'utilisation de textures si la scène
//*    doit comporter des objets non-texturés.
//*****************************************************************

	glEndList();
}



///////////////////////////////////////////////////////////////////////////////
// Construit un arbre dans une display-list.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_arbre()
{
	glNewList(ARBRE, GL_COMPILE);

		// On spécifie comme matériau courant celui correspondant au tronc d'arbre
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_tronc);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_tronc);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_tronc);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_tronc);

		glPushMatrix();						// On sauve la matrice modelview
		glRotatef(270, 1,0,0);				// Un rotation destinée à mettre dans le sens de y...
		glutSolidCone ( 1, 6, 15, 15);		// ...un cône
		glPopMatrix();						// On restaure la matrice modelview


		// On spécifie comme matériau courant celui correspondant au feuillage d'arbre
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_feuilles);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_feuilles);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_feuilles);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_feuilles);

		glPushMatrix();						// On sauve la matrice modelview
		glTranslatef(0, 6, 0);				// On translate au sommet du cône...
		glutSolidSphere(3, 20, 20);			// ...une sphère
		glPopMatrix();						// On restaure la matrice modelview

	glEndList();
}



///////////////////////////////////////////////////////////////////////////////
// Initialise la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void initialise_scene()
{
	charge_textures();						// Chargement des textures
	construit_maison();						// Création de la display list de la maison
	construit_arbre();						// Création de la display list de l'arbre
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
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation d'autres paramètres d'OpenGL
	initGL();

	// Initialisation de la scène
	initialise_scene();

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
