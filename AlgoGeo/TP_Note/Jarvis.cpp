#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#define PI 3.14159265

using namespace std;

const int absMin = 50;
const int absMax = 550;
const int ordMin = 150;
const int ordMax = 650;

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AffichagePoints(int n, std::vector<point> sommet){
  //Affichage de n points dont les coordonnees sont donnees dans sommet[n][2]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)

   ofstream output;
   output.open("PointsJarvis.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet.at(i).abscisse << " " << sommet.at(i).ordonnee << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet.at(i).abscisse+2 << " " << sommet.at(i).ordonnee << " moveto" <<endl;
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

void AffichageEnvConv(int n, std::vector<point> sommet, int envconv[]){
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
     output << sommet.at(i).abscisse << " " << sommet.at(i).ordonnee << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet.at(i).abscisse+2 << " " << sommet.at(i).ordonnee << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << endl;
    for(int i=0;i<n;i++){
      if(envconv[i+1]!=-1){
      output << sommet.at(envconv[i]).abscisse << " " << sommet.at(envconv[i]).ordonnee 
 	    << " moveto"  << endl;
      output << sommet.at(envconv[i+1]).abscisse << " " << sommet.at(envconv[i+1]).ordonnee 
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

void PointAuHasard(int n, std::vector<point> &sommet){
	srand(time(NULL));

	for(int i=0; i<n; i++){
		point p;
		p.abscisse = absMin + (rand() % (absMax - absMin));
		p.ordonnee = ordMin + (rand() % (ordMax - ordMin));
		sommet.push_back(p);
		//sommet[i].abscisse = absMin + (rand() % (absMax - absMin));
		//sommet[i].ordonnee = ordMin + (rand() % (ordMax - ordMin));
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

int Jarvis(int n, std::vector<point> sommet,int* envconv){

	int pMin, pCourant, pSuivant;
	int p = 1;
	int pos;
	int ind = 0;
	
	pMin = 0;
	for(int i=0; i<n; i++){
		if(sommet.at(i).ordonnee < sommet.at(pMin).ordonnee){
			pMin = i;
		}
	}

	pCourant = pMin;
	envconv[0] = pMin;
	//std::cout << "pMin : " << pMin << std::endl;
	
	do{	
		do{
			pSuivant = rand() % n;
		}while(pSuivant == pCourant);
		
		for(int i =0; i<n; i++){
			if(AnglePolaireInferieur(sommet.at(pCourant),sommet.at(pSuivant),sommet.at(i))){
				pSuivant = i;
			}
		}
		
		envconv[p] = pSuivant;
		pCourant = pSuivant;
		p++;
	
	
	}while( pCourant != pMin );
	
	envconv[p] = envconv[0];
	
	return p-1;
}

bool appartienEnvConv(int i,int n, int* envconv){
	
	for(int j=0; j<n; j++){
		if(envconv[j] == i){
			return true;
		}
	
	}
	return false;
}

void pelureOignon(int n, std::vector<point> sommet,int* envconv){

	int nbSommet;
	int pos;
	
	ofstream output;
	output.open("EnvConvJarvis.ps");//
	output << "%!PS-Adobe-3.0" << endl;
	output << endl; 
	 
	for(int i=0;i<n;i++){
		output << sommet.at(i).abscisse << " " << sommet.at(i).ordonnee << " 2 0 360 arc" <<endl;
		output << "0 setgray" <<endl;
		output << "fill" <<endl;
		output << sommet.at(i).abscisse+2 << " " << sommet.at(i).ordonnee << " moveto" <<endl;
		output << "/Courier findfont 15 scalefont setfont" << endl;
		output << "("<< i << ")" << " show" << endl;
		output << "stroke" << endl;
		output << endl;
	}
	output << endl;
	
	while( n >3){
	
		nbSommet = Jarvis(n,sommet,envconv);

		for(int i=0;i<n;i++){
			if(envconv[i+1]!=-1){
				output << sommet.at(envconv[i]).abscisse << " " << sommet.at(envconv[i]).ordonnee 
					 << " moveto"  << endl;
				output << sommet.at(envconv[i+1]).abscisse << " " << sommet.at(envconv[i+1]).ordonnee 
					<< " lineto"  << endl;
				output << "stroke" << endl;
				output << endl;
    			}
		}
		
		std::vector<point> nouveauSommet;
  	  
		for(int i=0; i<n; i++){
  	  		if( !appartienEnvConv(i,nbSommet,envconv) ){
  	  			nouveauSommet.push_back(sommet.at(i));
  	  		}
  	  	}
  	  	
  	  	for(int i=0;i<n+1;i++){envconv[i]=-1;}
  	  	
  	  	n = n - nbSommet;
  	  	
  	  	sommet = nouveauSommet;
  	  	
	}
	
	output << "showpage";
	output << endl;
	output.close();
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main(){

int n=20;

  std::vector<point> sommet;
  
  point p;
  
  p.abscisse = 123;
  p.ordonnee = 523;
  sommet.push_back(p);
  
p.abscisse=259;
p.ordonnee=476;
  sommet.push_back(p);
  
p.abscisse=411;
p.ordonnee=280;
sommet.push_back(p);
  
p.abscisse=60;
p.ordonnee=400;
sommet.push_back(p);
  
p.abscisse=187;
p.ordonnee=544;
sommet.push_back(p);
  
p.abscisse=447;
p.ordonnee=381;
sommet.push_back(p);

p.abscisse=296;
p.ordonnee=194;
sommet.push_back(p);

p.abscisse=273;
p.ordonnee=614;
sommet.push_back(p);

p.abscisse=130;
p.ordonnee=250;
sommet.push_back(p);

p.abscisse=212;
p.ordonnee=587;
sommet.push_back(p);

p.abscisse=500;
p.ordonnee=400;
sommet.push_back(p);

p.abscisse=280;
p.ordonnee=170;
sommet.push_back(p);

p.abscisse=280;
p.ordonnee=630;
sommet.push_back(p);

p.abscisse=311;
p.ordonnee=233;
sommet.push_back(p);

p.abscisse=345;
p.ordonnee=512;
sommet.push_back(p);

p.abscisse=130;
p.ordonnee=550;
sommet.push_back(p);

p.abscisse=430;
p.ordonnee=250;
sommet.push_back(p);

p.abscisse=212;
p.ordonnee=587;
sommet.push_back(p);

p.abscisse=430;
p.ordonnee=550;
sommet.push_back(p);

p.abscisse=431;
p.ordonnee=450;
sommet.push_back(p);

  int envconv[n+1];  
  for(int i=0;i<n+1;i++){envconv[i]=-1;}
  AffichagePoints(n,sommet);
  
  pelureOignon(n,sommet,envconv);
  //Jarvis(n,sommet,envconv);
  //AffichageEnvConv(n,sommet,envconv);
}
