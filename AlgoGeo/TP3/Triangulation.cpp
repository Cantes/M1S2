#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#define PI 3.14159265

using namespace std;

int const n=50;


/*******************************************************************/
// Structure point
/*******************************************************************/

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;



/*******************************************************************/
// Structure triangle
/*******************************************************************/

//structure triangle, pour une variable triangle  T, ses sommets sont accessibles par
//T.a, T.b et T.c

typedef struct {
  int a;
  int b;
  int c;
} triangle;

/*******************************************************************/
//Petites fonctions arithmetiques ou geometriques
/*******************************************************************/


int det(point p0, point p1, point p2, point p3){
//Renvoie le determinant de p0p1,p2p3
  return (p1.abscisse-p0.abscisse)*(p3.ordonnee-p2.ordonnee)-(p1.ordonnee-p0.ordonnee)*(p3.abscisse-p2.abscisse);
}

int ProduitScalaire(point p0, point p1, point p2, point p3){
//Renvoie le produit scalaire de p0p1,p2p3
  return (p1.abscisse-p0.abscisse)*(p3.abscisse-p2.abscisse)+(p1.ordonnee-p0.ordonnee)*(p3.ordonnee-p2.ordonnee);
}

int Carre(int x){
  return x*x;
}

int NormeAuCarre(point p1, point p2){
  //Calcul la norme au carre de p1p2
  return Carre(p1.ordonnee-p2.ordonnee)+Carre(p1.abscisse-p2.abscisse);
}

bool EstADroite(point A, point B, point C){
  //Renvoie vrai si C est strictement a droite de (AB) oriente de A vers B.
  if(det(A,B,A,C)>=0){return false;}
  else{return true;}
}

/*******************************************************************/
//Generation de sommets au hasard
/*******************************************************************/

void PointAuHasard(int n, point sommet[]){
  //Tire n points au hasard uniformement repartis dans un disque, leurs coordonnees sont
  //stockees dans sommet[]
  int tps=time(NULL);
  //cout << "graine :"<< tps <<endl;
  srand(time(NULL));//1363192482);//tps);
  for(int i=0;i<n;i++){
    int r= rand()%250;
    int theta= rand() %360;
    sommet[i].abscisse=(int) (300 +r*cos( (float)theta /180.0 * PI ));
    sommet[i].ordonnee=(int) (400 + r*sin((float)theta /180.0 * PI ));
  }
}


/*******************************************************************/
//Fonctions d'affichage
/*******************************************************************/


/*******************************************************************/
//Fonctions d'affichage
/*******************************************************************/

void AffichagePoints(int n, point sommet[]){
  //Affichage de n points dont les coordonnees sont dans sommet[n]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview)
   ofstream output;
   output.open("Points.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i].abscisse << " " << sommet[i].ordonnee << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet[i].abscisse+2 << " " << sommet[i].ordonnee << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << "showpage";
   output << endl;
   output.close();
}

//void AffichageTriangulation(int n, point sommet[], int t, triangle T[]){
void AffichageTriangulation(int n, point sommet[], int t, std::vector<triangle> T){
  //Affichage des n points du plan dont les coordonnees sont dans sommet[] et d'une triangulation
  //en t triangles stockes dans T, tableau de taille t.
  //Produit en sortie un fichier Triangulation.ps
  
   ofstream output;
   output.open("Triangulation.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i].abscisse << " " << sommet[i].ordonnee << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet[i].abscisse+2 << " " << sommet[i].ordonnee << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << endl;
    for(int i=0;i<T.size();i++){
      output << sommet[T.at(i).a].abscisse << " " << sommet[T.at(i).a].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T.at(i).b].abscisse << " " << sommet[T.at(i).b].ordonnee
 	    << " lineto"  << endl;
      output << sommet[T.at(i).b].abscisse << " " << sommet[T.at(i).b].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T.at(i).c].abscisse << " " << sommet[T.at(i).c].ordonnee
 	    << " lineto"  << endl;
      output << sommet[T.at(i).c].abscisse << " " << sommet[T.at(i).c].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T.at(i).a].abscisse << " " << sommet[T.at(i).a].ordonnee
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
    }
    output << "showpage";
    output << endl;
    output.close();
}


/************************************************************************/
//Calcul de la triangulation
/************************************************************************/

void TriLexicographique(int n, point* sommet, int t, int* Tri){
  //En entree, Tri, tableau de taille n, contient les indices des sommets a trier, a l'initialisation
  //Tri[i]=i, et t est la taille de Tri, donc t=n pour le premier appel.
  //En sorti, Tri contient les indices des sommets tries par ordre lexicographique croissant. 
  if(t>1){
    int pivot=Tri[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if((sommet[Tri[0]].abscisse<sommet[Tri[i]].abscisse)||
	 ((sommet[Tri[0]].abscisse==sommet[Tri[i]].abscisse)&&
	  (sommet[Tri[0]].ordonnee<sommet[Tri[i]].ordonnee))){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td
    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if((sommet[Tri[0]].abscisse<sommet[Tri[i]].abscisse)||
	 ((sommet[Tri[0]].abscisse==sommet[Tri[i]].abscisse)&&
	  (sommet[Tri[0]].ordonnee<sommet[Tri[i]].ordonnee))){//A droite
      Td[indice_droit]=Tri[i];
      indice_droit++;}
      else{//A gauche
      Tg[indice_gauche]=Tri[i];
      indice_gauche++;}}

    //On trie Td et Tg
    if(d>1){TriLexicographique(n,sommet,d,Td);}
    if(t-d-1>1){TriLexicographique(n,sommet,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}




int TriangulIncrementale(int n, point* sommet, int* tri, std::vector<triangle> &T){
  
	int j;
	int Kdroite, Kgauche;
	std::vector<int> envconv;
	
 	triangle T0;
 	T0.a = tri[0];
 	T0.b = tri[1];
 	T0.c = tri[2]; 
 	
 	T.push_back(T0);

 	envconv.push_back(T0.c);
 	
 	 if( sommet[T0.b].ordonnee > sommet[T0.a].ordonnee){
 	
 		envconv.push_back(T0.b); 
 		envconv.push_back(T0.a); 
 	}else{
		envconv.push_back(T0.a);
		envconv.push_back(T0.b); 
 	}

 	envconv.push_back(T0.c);
 	
 	
	for(int i=2;i<n-1;i++){
	
		j = 0;
		
		while(det(sommet[tri[i+1]],sommet[envconv.at(j)],sommet[tri[i+1]],sommet[envconv.at(j+1)] ) < 0){		
			
			triangle t;
			t.a = envconv.at(j);
			t.b = envconv.at(j+1);
			t.c = tri[i+1];	
			
			T.push_back(t);

			j++;
		}
		
		Kdroite = j;
		
		j = envconv.size()-1;
		
		while(det(sommet[tri[i+1]],sommet[envconv.at(j)],sommet[tri[i+1]],sommet[envconv.at(j-1)]) > 0){
			
			triangle t;

			t.a = envconv[j];
			t.b = envconv[j-1];
			t.c = tri[i+1];
			
			T.push_back(t);
			
			j--;
		
		}
		
		Kgauche = j;
		
		
		std::vector<int> envconvTmp;
		
		envconvTmp.push_back(tri[i+1]);
		
		for (int i = Kdroite; i < Kgauche+1; ++i) {
			envconvTmp.push_back(envconv.at(i));
		}
		
		envconvTmp.push_back(tri[i+1]);
		
		envconv = envconvTmp;
		
		/*
		for(int i=0; i< envconv.size(); i++){
			std::cout << envconv.at(i) << std::endl;
		
		}
		
		std::cout << std::endl;*/

 	}
 	
	return T.size();
}

/*******************************************************************/
//main
/*******************************************************************/


int main(){
  point sommet[n];
  int tri[n];
  std::vector<triangle> T;
 // triangle T[3*n];
  for(int i=0;i<n;i++){tri[i]=i;}
  PointAuHasard(n,sommet);
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);
  AffichageTriangulation(n,sommet,t,T);
  }

