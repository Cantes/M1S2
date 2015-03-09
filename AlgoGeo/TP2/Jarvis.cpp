#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

using namespace std;

int const n=30;
const int absMin = 50;
const int absMax = 550;
const int ordMin = 150;
const int ordMax = 650;

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AffichagePoints(int n, point sommet[]){
  //Affichage de n points dont les coordonnees sont donnees dans sommet[n][2]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)

   ofstream output;
   output.open("PointsJarvis.ps");//
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AffichageEnvConv(int n, point sommet[], int envconv[]){
//Affichage de n points dont les coordonnees sont donnees dans sommet[n][2] et de leur
  //enveloppe convexe donnee sous forme de liste cyclique: un tableau de taille n+1 listant les
  //indices des sommets de l'enveloppe convexe. Le premier sommet est repete en fin de liste et le
  //tableau est complete par la valeur -1.
  //Un fichier EnvConv.ps est cree


   ofstream output;
   output.open("EnvConvJarvis.ps");//
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
    for(int i=0;i<n;i++){
      if(envconv[i+1]!=-1){
      output << sommet[envconv[i]].abscisse << " " << sommet[envconv[i]].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[envconv[i+1]].abscisse << " " << sommet[envconv[i+1]].ordonnee 
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
    }
    }
    output << "showpage";
    output << endl;
    output.close();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Generation au hasard dans un cercle de l'ensemble des points consideres

void PointAuHasard(int n, point sommet[]){
	srand(time(NULL));

	for(int i=0; i<n; i++){
		sommet[i].abscisse = absMin + (rand() % (absMax - absMin));
		sommet[i].ordonnee = ordMin + (rand() % (ordMax - ordMin));
	}

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Renvoie Vrai si p3 est strictement a droite de la droite p_1p_2
bool AnglePolaireInferieur(point p1, point p2, point p3){
	if( ((p3.abscisse-p1.abscisse)*(p2.ordonnee-p1.ordonnee) - (p3.ordonnee-p1.ordonnee)*(p2.abscisse-p1.abscisse)) > 0 ){
		return true;
	}else{
		return false;
	}
}

//Parcours de Jarvis

void Jarvis(int n, point* sommet,int* envconv){

	int pMin, pCourant, pSuivant;
	int p = 1;
	int pos;
	int ind = 0;
	
	pMin = 0;
	for(int i=0; i<n; i++){
		if(sommet[i].ordonnee < sommet[pMin].ordonnee){
			pMin = i;
		}
	}

	pCourant = pMin;
	envconv[0] = pMin;
		
	do{	
		do{
			pSuivant = rand() % n;
		}while(pSuivant == pCourant);
		
		for(int i =0; i<n; i++){
			if(AnglePolaireInferieur(sommet[pCourant],sommet[pSuivant],sommet[i])){
				pSuivant = i;
			}
		}
		
		envconv[p] = pSuivant;
		pCourant = pSuivant;
		p++;
	
	
	}while( pCourant != pMin );
	
	envconv[p] = envconv[0];

}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main(){
  point sommet[n];
  int envconv[n+1];
  for(int i=0;i<n+1;i++){envconv[i]=-1;}
  PointAuHasard(n,sommet);
  AffichagePoints(n,sommet);
  Jarvis(n,sommet,envconv);
  AffichageEnvConv(n,sommet,envconv);
}
