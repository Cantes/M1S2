#include <iostream>
#include <fstream>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265
#include <stdlib.h>

using namespace std;

int const n=20;

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AffichagePoints(int n, point sommet[]){
  //Affichage de n points dont les coordonnees sont donnees dans sommet[n][2]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)

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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AffichageEnvConv(int n, point sommet[], int envconv[]){
//Affichage de n points dont les coordonnees sont donnees dans sommet[n][2] et de leur
  //enveloppe convexe donnee sous forme de liste cyclique: un tableau de taille n+1 listant les
  //indices des sommets de l'enveloppe convexe. Le premier sommet est repete en fin de liste et le
  //tableau est complete par la valeur -1.
  //Un fichier EnvConv.ps est cree


   ofstream output;
   output.open("EnvConv.ps");//
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


//Renvoie Vrai si p2 est strictement a droite de la droite oriente p_0p_1
bool AnglePolaireInferieur(point p0, point p1, point p2){

  //
  // A COMPLETER
  //

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void TriRapidePolaire(int min, int n, point sommet[], int t, int TriPolaire[]){
  //t: nombre d elements a trier, au premier appel on fait donc:
  // Tripolaire(min,n,sommet,n-1,TriPolaire);
  //ou TriPolaire contient les indeices des sommets a trier (tous sauf min).

  if(t>1){
    int pivot=TriPolaire[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if(AnglePolaireInferieur(sommet[min],sommet[pivot],sommet[TriPolaire[i]])){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td

    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if(AnglePolaireInferieur(sommet[min],sommet[pivot],sommet[TriPolaire[i]])){//A droite
      Td[indice_droit]=TriPolaire[i];
      indice_droit++;}
      else{//A gauche
      Tg[indice_gauche]=TriPolaire[i];
      indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriRapidePolaire(min,n,sommet,d,Td);}
    if(t-d-1>0){TriRapidePolaire(min,n,sommet,t-d-1,Tg);}
    //Fusion dans TriPolaire
    for(int i=0;i<t;i++){
      if(i<d){TriPolaire[i]=Td[i];}
      if(i==d){TriPolaire[i]=pivot;}
      if(i>d){TriPolaire[i]=Tg[i-d-1];}
    }
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void PointAuHasard(int n, point sommet[]){
  srand(time(NULL));

  //
  // A COMPLETER
  //


}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Graham(int n, point sommet[],int envconv[]){

  //
  // A COMPLETER
  //

  }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main(){
  point sommet[n];
  int envconv[n+1];
  for(int i=0;i<n+1;i++){envconv[i]=-1;}
  PointAuHasard(n,sommet);
  
  Graham(n,sommet,envconv);
  AffichageEnvConv(n,sommet,envconv);
 
}
