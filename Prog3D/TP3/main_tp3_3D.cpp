#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <iostream>"

using namespace std;

#include <GL/freeglut.h>

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


//nbPoints du tableau



// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//affcihage points et vecteurs (tp1)
void dessinePoint (const Point& p, int taille);
void dessineVector (const Point& p, Vector& v);
void dessineDroite(Point p1, Point p2);

//affichage courbe (tp2)
void drawCurve(const Point* tabPointsOfCurve, const long nbPoints);
void drawPoints(const Point* tab, const long nbPoints);
//Bezier curve
double Fact(double val);

Point* BezierCurve(Point* tabControlePoint, long nbControlPoint, long nbU);
Point* getPosCasteljau(Point* tabControlPoint,long nbControlPoint, double u);
Point getPosCasteljau2(Point p1, Point p2, double u);
Point* BezierCurveByCasteljau(Point* tabControlPoint, long nbControlPoint, long nbU);

//surfaces

void drawSurfaceCylindric (Point* courbe, Vector v, int U, int V);
void dessineDroite(Point p1, Point p2);
void drawSurfaceReglee(Point* courbe1, Point* courbe2, int U, int V);
void drawSurfaceByCasteljau(Point** matrice, int nbPointControlU, int nbPointControlV, double u, double v);
Point** getMatrice(Point* tabControlPointU, long nbPointControlU,Point* tabControlPointV, long nbPointControlV);
Point** getMatricePlusPetite(Point** matrice, double u, double v, int nbu, int nbv);

void afficheMatrice(Point** matrice, int tailleU, int tailleV);


int main(int argc, char **argv)
{
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

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
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
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

GLvoid window_reshape(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) {
  case KEY_ESC:
    exit(1);
    break;

  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
 glColor3f(1.0, 1.0, 1.0);


Point* tab = new Point [6];


tab [0] = Point (-1.1,1,0);
tab [1] = Point (-0.1,1.7,0);
tab [2] = Point (0.5,1,0);
tab [3] = Point (1.2,1.6,0);
tab [4] = Point (1.7,0.8,0);
tab [5] = Point (2,1.5,0);
/*tab [6] = Point (0.2,0.8,0);
tab [7] = Point (0.4,0.6,0);
tab [8] = Point (0.6,0.4,0);
tab [9] = Point (0.8,0.2,0);*/
//drawCurve(tab,6);
//glColor3f(1.0, 0, 1.0);


/*Point* tab1 = new Point [4];
tab1 [0] = Point (-1.7,0.7,0);
tab1 [1] = Point (-1.7,0.3,0);
tab1 [2] = Point (-1.7,0,0);
tab1 [3] = Point (-1.7,-0.3,0);*/

//jeus de tests
Point* testU = new Point [4];
testU[0] = Point(-1,0,0);
testU[1] = Point(-0.5,1,0);
testU[2] = Point(0,0,0);
testU[3] = Point(0.5,1,0);
//glColor3f(1.0, 1.0, 0);//jaune
//drawCurve(testU,4);

Point* testV = new Point[3];
testV[0] = Point(-1,0,0);
testV[1] = Point(-1,-0.5,0);
testV[2] = Point(-1,-1,0);
//glColor3f(1.0, 0, 1.0);//rose
//drawCurve(testV,3);
Point** mat = getMatrice(testU,4,testV,3);
afficheMatrice(mat,4,3);
drawSurfaceByCasteljau(mat,4,3,4,3);

/*glColor3f(1.0, 1.0, 0);//jaune
//drawCurve(tab,6);

glColor3f(1.0, 0, 1.0);//rose
drawCurve(tab1,4);*/

/*//création d'une matrice test
Point a = Point (0,0,0);
Point b = Point (0.5,0,0);
Point c = Point (1,0,0);
Point d = Point (0,-0.5,0);
Point e = Point (0.5,-0.5,0);
Point f = Point (1,-0.5,0);*/

/*glColor3f(1.0, 1.0, 1.0);//blanc
Point** mat = getMatrice(tab,6,tab1,4);
//afficheMatrice(mat,6,4);

drawSurfaceByCasteljau(mat,6,4,5,3);*/
}

//Point** createMatrice(double increment)
//{
  //  Point*
//}

//====================fonctions tp1============================
void dessinePoint(const Point& p, int taille)
{
   glPointSize(taille);
    glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POINTS);
   glVertex3f(p.getX(),p.getY(),p.getZ());
   glEnd();
}


void dessineVector(const Point& p, Vector& v)
{
    glBegin(GL_LINES);
    glVertex3f(p.getX(), p.getY(), p.getZ());
    glVertex3f(p.getX()+v.getX(), p.getY()+v.getY(), p.getZ()+v.getZ());
    glEnd();
}

//===================fonctions tp2==============================
void drawCurve(const Point* tab, const long nbPoints)
{
    glBegin(GL_LINE_STRIP);
    for (int i =0 ; i<nbPoints ; i++){
       glVertex3f(tab[i].getX(),tab[i].getY(),tab[i].getZ());}
    glEnd();

    /*for (int i =0; i <nbPoints; i++){
       dessinePoint(tab[i],1);}*/
}

void drawPoints(const Point* tab, const long nbPoints)
{
    for (int i =0; i <nbPoints; i++)
    {
       dessinePoint(tab[i],3);
    }
}



double Fact(double n) {
	if (n == 0) {
		return 1.0;
	}
	return n*Fact(n-1);
}


double Newton(long nbControlPoint, int CurrentControlPoint, double u)
{
    int n = nbControlPoint;
    int i = CurrentControlPoint;
   double b = (Fact(n)/(Fact(i)*Fact(n-i)))*pow(u,i)*pow((1-u),(n-i));
   return b;
}

Point* BezierCurve(Point* tabControlPoint, long nbControlPoint, long nbU)
{

	double n = nbControlPoint-1;
	Point* pts = new Point[nbU];

	for (int j = 0; j < nbU; ++j) {
		double u = 1.0/(nbU-1) * (double) j;
		Point p = Point();
		for (int i = 0; i <= n; ++i) {
			double Bni = (Fact(n) / (Fact(i) * Fact(n-i))) * pow(u, i) * pow(1-u, n-i);
			p.setX(p.getX() + Bni*tabControlPoint[i].getX());
			p.setY(p.getY() + Bni*tabControlPoint[i].getY());
			p.setZ(p.getZ() + Bni*tabControlPoint[i].getZ());
		}
		pts[j] = p;
	}
	return pts;
}



Point getPosCasteljau2(Point p1, Point p2, double u)
{

    Vector v =p1.createVector(p2);
  //  v.afficher();
    Point p = Point ();
   // v.Normalized();
    p= p1.multiply(v,u);

    if(u == 0.3)
    {
dessineDroite(p1,p2);
    }
    return p ;
}

Point* getPosCasteljau(Point* tabControlPoint,long nbPtCont, double u)
{
    //s'il n'ya qu'un seul point de controle le piont final prendra sa valeur
//Point* tab1 = new Point [1];
 Point* res = new Point[(int)nbPtCont-1];
if (nbPtCont == 1)
{

    return tabControlPoint;
   //  return tab1;
}


else
{

   for (int i =0;i<nbPtCont-1;i++)
   {
       Point p1 = tabControlPoint[i];
       Point p2 = tabControlPoint[i+1];
       Point p12 = getPosCasteljau2(p1,p2,u);
        res [i] = p12;

        if(u == 0.3)
        {



       // glVertex3f(p12.getX(),p12.getY(),p12.getZ());
        }
}

   return getPosCasteljau(res,nbPtCont-1,u);
}
}

Point* BezierCurveByCasteljau(Point* tabControlPoint, long nbControlPoint, long nbU)
{
    //int n = nbControlPoint-1;
    //création du tableau qui contiendra les nouveaux points.
    Point* res = new Point[nbU];
    for (int i=1;i<=nbU;i++)
    {
        double u = (double)i/nbU;
        Point* tab = getPosCasteljau(tabControlPoint,nbControlPoint,u);
        res[i] = tab[0];
    }
return res;
}

void dessineDroite(Point p1, Point p2)
{
   glBegin(GL_LINES);
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glEnd();
}


void drawSurfaceCylindric(Point* courbe, Vector vec, int U, int V)
{

	Point* res = new Point [U*V];
    for (int i = 0; i<U; i++)
    {
        Point pu = courbe [i];
        Point qu = pu.addit(vec);
        for( int j = 0; j < V; j ++)
        {
            double v = (double)j/V;
            double X = (1-v) * pu.getX() + v * qu.getX();
            double Y = (1-v) * pu.getY() + v * qu.getY();
            double Z = (1-v) * pu.getZ() + v * qu.getZ();
      Point p = Point( X, Y, Z);
      res[j] = p;
        }
        drawPoints(res,4);
    }
}

void drawSurfaceReglee(Point* courbe1, Point* courbe2, int U, int V)
{
    Point* res = new Point [U*V];
    for (int i = 0; i<U; i++)
    {
        double u = (double)(i/U-1);
        Point pu = courbe1[i];
        Point qu = courbe2[i];

        for (int j = 0; j<V;j++)
        {
            double v = (double)j/V;
            double X = (1-v) * pu.getX() + v * qu.getX();
            double Y = (1-v) * pu.getY() + v * qu.getY();
            double Z = (1-v) * pu.getZ() + v * qu.getZ();
      Point p = Point( X, Y, Z);
      res[j] = p;
        }
         drawPoints(res,V);
    }
}

Point** getMatrice(Point* tabControlPointU, long nbPointControlU,Point* tabControlPointV, long nbPointControlV)
{
    //création d'une matrice vide
    Point** matrice = new Point* [nbPointControlU];
    for(int k =0;k<nbPointControlU;k++){
        matrice[k] = new Point [nbPointControlV];}

//remplissage de la matrice ptV sur les Y et ptU sur les X
//on récup le vecteur entre le 1er pt de V et le 1er pt de U et on le récypérera pour touts les U
    for(int i =0; i < nbPointControlU;i++)
    {
        Point pU = tabControlPointU[i];
        Point pV = tabControlPointV[0];
        Vector trans = pV.createVector(pU);
//ensuite on fait une translation de tous les points v de ce même vecteur pour former un quadrillage
        for( int j =0; j<nbPointControlV;j++)
        {
           //dessineVector(tabControlPointV[j],trans);
           matrice[i][j] = tabControlPointV[j].addit(trans);
           dessinePoint(matrice[i][j],1);
        }
    }
return matrice;// fonction ok
}

Point** getMatricePlusPetite(Point** matrice, double u, double v, int nbX, int nbY)
{
    cout << "nbX=" << nbX << endl;
 cout << "nbY=" << nbY << endl;
    //if(nbX==1 && nbY==0){
    if(nbX==2 && nbY==1){
            //faire casteljaucurve sur les deux points
          Point* deuxPtRestant = new Point[2];
          deuxPtRestant[0] = matrice[0][0];
          deuxPtRestant[1] = matrice[1][0];



        return matrice;}

//création de la matrice
    Point** matricePetite = new Point* [nbX];
    for(int n =0;n<nbX-1;n++){
        matricePetite[n] = new Point[nbY];}

    for(int i =0;i<nbX-1;i++)
    {
        for(int j = 0;j< nbY-1;j++)
        {     cout<<"i="<<i<<endl;

           cout<<"j="<<j<<endl;

            Point pij = matrice[i][j];
            Point piPlus = matrice [i+1][j];
            Point pijPlus = matrice [i+1][j+1];
            Point pjPlus = matrice [i][j+1];
            Vector A = pij.createVector(piPlus);
/*A.afficher();glColor3f(0.6, 0.3, 1.0);//violet foncé
dessineVector(pij,A);*/
            Vector B = pjPlus.createVector(pijPlus);
/*glColor3f(0, 0.3, 1.0);//bleu roi
dessineVector(pjPlus,B);//B.afficher();*/
            Point a = pij.multiply(A,u);
/*glColor3f(1.0, 1.0, 0);//jaune
dessinePoint(a,1);*/
            Point b = pjPlus.multiply(B,u);
            Vector AB = a.createVector(b);
/*glColor3f(1.0, 1.0, 0);//jaune
dessineVector(a,AB);*/
            Point m = a.multiply(AB,v);
dessinePoint(m,1);
//m.afficher();
            matricePetite[i][j] = m;
         cout<<"fin"<<endl;
        }
    }
    cout<<"matricepluspetitefini"<<endl;
    return getMatricePlusPetite(matricePetite,u,v,nbX-1,nbY-1);
}

void drawSurfaceByCasteljau(Point** matrice, int nbPointControlU, int nbPointControlV, double nbu, double nbv)
{
    for(int i= 0; i<nbu;i++)
    {
  //      cout<<"i="<<i<<endl;
        for(int j =0;j<nbv;j++)
        {
//cout<<"j="<<j<<endl;
            double u = (double)(i/nbu-1);
            double v = (double)(j/nbv-1);
            matrice = getMatricePlusPetite(matrice, u,v,nbPointControlU,nbPointControlV);
            cout<<"hello"<<endl;
            matrice[0][0].afficher();
            dessinePoint(matrice[0][0],1);
        }
    }
}

void afficheMatrice(Point** matrice, int tailleU, int tailleV)
{
    glPointSize(5);
    glBegin(GL_POINTS);

    for(int i =0; i<tailleU;i++){
        for(int j =0;j<tailleV;j++){
            glVertex3f(matrice[i][j].getX(),matrice[i][j].getY(),matrice[i][j].getZ());}}
     glEnd();
}



