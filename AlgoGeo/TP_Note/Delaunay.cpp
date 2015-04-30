#include <iostream>
#include <fstream>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265
#include <stdlib.h>
#include <vector>

using namespace std;

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

//------------------------------

int ProduitScalaire(point p0, point p1, point p2,point p3){

//Renvoie le produit scalaire de p0p1,p2p3

  return (p1.abscisse-p0.abscisse)*(p3.abscisse-p2.abscisse)+(p1.ordonnee-p0.ordonnee)*(p3.ordonnee-p2.ordonnee);
}

//------------------------------

int  Carre (int x){
  return x*x;}

//-----------------------------

int NormeAuCarre(point p1,point p2){

  //Calcul la norme au carre de p1p2

  return Carre(p1.ordonnee-p2.ordonnee)+Carre(p1.abscisse-p2.abscisse);
}

//------------------------------

bool EstADroite(point A, point B, point C){
  //Renvoie vrai si C est strictement a droite de (AB) oriente de A vers B.
  if(det(A,B,A,C)>=0){return false;}
  else{return true;}
}


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
       output << "stroke" << endl;
     output << endl;
   }
   output << "showpage";
   output << endl;
   output.close();
}

//-------------------------------------

void AffichageTriangulation(bool delo, int n, point sommet[], int t, std::vector<triangle> T){

  //Affichage des n points du plan dont les coordonnees sont dans sommet[] et 
  //d'une triangulation en t triangles stockes dans T, tableau de taille t.
  // si delo est a true, on ecrit Delaunay.ps, sinon Incremental.ps
   ofstream output;
   if(!delo){output.open("Incremental.ps");}else{
     output.open("Delaunay.ps");}

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
    for(int i=0;i<t;i++){
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

/*******************************************************************/
//Generation de sommets au hasard
/*******************************************************************/

void PointAuHasard(int n,point sommet[]){

  //Tire n points au hasard uniformement repartis dans un disque, leurs coordonnees sont
  //stockees dans sommet[]
  int graine=time(NULL);
  //int tps = 256;
  srand(graine);
 // srand(tps);
  for(int i=0;i<n;i++){
    int r= rand()%250;
    int theta= rand() %360;
    sommet[i].abscisse=(int) (300 +r*cos( (float)theta /180.0 * PI ));
    sommet[i].ordonnee=(int) (400 + r*sin((float)theta /180.0 * PI ));
  }
}

/*******************************************************************/
//Reperer un point par rapport au cercle circonscrit a un triangle
/*******************************************************************/

bool MemeCote(point A, point B, point C, point D){

  //Renvoie vrai si C et D sont du meme cote de (AB).

  if((det(A,B,A,C)*det(A,B,A,D))>0){return true;}
  else{  return false;}
}

//----------------------------------------

bool StrictementDansLeCercleCirconscritMemeCote(point A, point B, point C, point D){

  //Renvoie vrai si D est strictement dans le cercle circonscrit de ABC.
  //On suppose C et D du meme cote de (AB).
  //Faire un test entier

  long long adb= ProduitScalaire(D,A,D,B); //attention aux depassement d'entier
  long long acb= ProduitScalaire(C,A,C,B);
  long long ac2= NormeAuCarre(A,C);
  long long ad2= NormeAuCarre(A,D);
  long long bc2= NormeAuCarre(B,C);
  long long bd2= NormeAuCarre(B,D);

  //
  //A COMPLETER
  //
  //Rq: ne pas utiliser la fonction Carre ici, on peut avoir des depassements d entier...


}

//---------------------------------------

int CentreCercleCirconscrit(point A, point B, point C, point* O){

	if(det(A,B,A,C)==0){
		return 1;
	}
	
	int xa=A.abscisse; int ya=A.ordonnee;
	int xb=B.abscisse; int yb=B.ordonnee;
	int xc=C.abscisse; int yc=C.ordonnee;
	
	(*O).abscisse=(int)((float)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(A,B,B,C)));
	(*O).ordonnee=(int)((float)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(B,C,A,B)));
	
	return 0;
}



bool StrictementDansLeCercleCirconscrit(point A, point B, point C, point D){

	point centreCercle;
	int result;
	
	result = CentreCercleCirconscrit(A,B,C, &centreCercle);
	
	if(result == 1){
		return false;
	}
	
	return (  sqrt( pow( A.abscisse - centreCercle.abscisse ,2) + pow( A.ordonnee - centreCercle.ordonnee ,2))
			>
		  sqrt( pow( D.abscisse - centreCercle.abscisse ,2) + pow( D.ordonnee - centreCercle.ordonnee ,2))
	       );


}

/************************************************************************/
//Calcul d'une premiere triangulation (algo incremental par ex)
/************************************************************************/


void TriLexicographique(int n, point sommet[], int t, int Tri[]){
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
    if(d>0){TriLexicographique(n,sommet,d,Td);}
    if(t-d-1>0){TriLexicographique(n,sommet,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}

//----------------------------------------


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
		
		for (int l = Kdroite; l < Kgauche+1; l++) {
			envconvTmp.push_back(envconv.at(l));
		}
		
		envconvTmp.push_back(tri[i+1]);
		
		envconv = envconvTmp;
		
 	}
 	

 	
	return T.size();
}

/*******************************************************************/
//Triangulation de Delaunay
/*******************************************************************/

bool TrianglesAdjacents(triangle s, triangle t){

  //renvoie vrai si s et t ont une arete en commun

  int sommet_commun=0;
  if((s.a==t.a)||(s.a==t.b)||(s.a==t.c)){sommet_commun++;}
  if((s.b==t.a)||(s.b==t.b)||(s.b==t.c)){sommet_commun++;}
  if((s.c==t.a)||(s.c==t.b)||(s.c==t.c)){sommet_commun++;}
  if(sommet_commun>=2){return true;}
  return false;
}

//-------------------------------------------

void TrianglesVoisins(int t, std::vector<triangle> T, int voisin[][3]){
 
  //Calcul pour chaque triangle les indices des triangles qui lui sont adjacents

	for(int i=0;i<t;i++){
	
		for(int j=0;j<i;j++){
		
			if(TrianglesAdjacents(T.at(i),T.at(j))){
			
				int case_libre;
				if(voisin[i][0]==-1){
					case_libre=0;
				}else{
					if(voisin[i][1]==-1){
						case_libre=1;
					}else{
						case_libre=2;
					}
				}
				
				voisin[i][case_libre]=j;
				
				if(voisin[j][0]==-1){
					case_libre=0;
				}else{
					if(voisin[j][1]==-1){
						case_libre=1;
					}else{
						case_libre=2;
					}
				}
				
				voisin[j][case_libre]=i;
      			}
		}
	}
}
     
//-------------------------------------------

int TroisiemePoint(triangle s, triangle t){

  //Renvoie l'indice du point de s qui n'est pas dans t

  if((s.a!=t.a)&&(s.a!=t.b)&&(s.a!=t.c)){return s.a;}
  if((s.b!=t.a)&&(s.b!=t.b)&&(s.b!=t.c)){return s.b;}
  if((s.c!=t.a)&&(s.c!=t.b)&&(s.c!=t.c)){return s.c;}
  return -1;
}

//---------------------------------------------

int TriangleArete(int i, int x, int y, std::vector<triangle> T, int voisin[][3]){

  //Renvoie le second triangle de T ayant xy comme arete (T[i] etant le premier)

  for(int k=0;k<3;k++){
    if(voisin[i][k]==-1){continue;}//on tape de l'autre cote de l'enveloppe convexe
    if((T.at(voisin[i][k]).a == x) && ((T.at(voisin[i][k]).b == y) || (T.at(voisin[i][k]).c == y))){
      return voisin[i][k];}
    if((T.at(voisin[i][k]).b == x) && ((T.at(voisin[i][k]).a == y) || (T.at(voisin[i][k]).c == y))){
      return voisin[i][k];}
    if((T.at(voisin[i][k]).c == x) && ((T.at(voisin[i][k]).b == y) || (T.at(voisin[i][k]).a == y))){
      return voisin[i][k];}
  }
  return -1;

}

int positionSommet(point* sommet,int n, point p){

	for(int i=0; i<n; i++){
		if(sommet[i].abscisse == p.abscisse && sommet[i].ordonnee == p.ordonnee){
			return i;
		}  
	}
	
	return -1;


}

//---------------------------------------------

void Flip(point* sommet,int n, int i, int j, std::vector<triangle> &T, int voisin[][3]){

  //Effectue un 'flip' entre les triangles T[i] et T[j]
  //t est la taille du tableau T et voisin, tableau calcule
  //par la fonction TrianglesVoisins, sera mis-a-jour

	int vieux_voisins_Ti[3]={voisin[i][0],voisin[i][1],voisin[i][2]};
	int vieux_voisins_Tj[3]={voisin[j][0],voisin[j][1],voisin[j][2]};
	int x=TroisiemePoint(T.at(i),T.at(j));// On nomme les 4 sommets
	int y=TroisiemePoint(T.at(j),T.at(i));
	int z;
	int w;

	std::cout << "Triangle 1 : " << T.at(i).a << "," << T.at(i).b << "," << T.at(i).c << std::endl;
	std::cout << "Triangle 2 : " << T.at(j).a << "," << T.at(j).b << "," << T.at(j).c << std::endl;
	
	if(T.at(i).a==x){
		z=T.at(i).b;
		w=T.at(i).c;
std::cout << "Flip entre les aretes formees par les sommets : " << positionSommet(sommet,n, sommet[z]) << "," << positionSommet(sommet,n, sommet[w]) << std::endl;
		std::cout << "par : " << std::endl;
std::cout << positionSommet(sommet,n, sommet[x]) << "," << positionSommet(sommet,n, sommet[y]) << std::endl;
	}
	
  	if(T.at(i).b==x){
  		z=T.at(i).a;
  		w=T.at(i).c;
std::cout << "Flip entre les aretes formees par les sommets : " << positionSommet(sommet,n, sommet[z]) << "," << positionSommet(sommet,n, sommet[w]) << std::endl;
		std::cout << "par : " << std::endl;
std::cout << positionSommet(sommet,n, sommet[x]) << "," << positionSommet(sommet,n, sommet[y]) << std::endl;
  	}
  	
  	if(T.at(i).c==x){
  		z=T.at(i).a;
  		w=T.at(i).b;
std::cout << "Flip entre les aretes formees par les sommets : " << positionSommet(sommet,n, sommet[z]) << "," << positionSommet(sommet,n, sommet[w]) << std::endl;
		std::cout << "par : " << std::endl;
std::cout << positionSommet(sommet,n, sommet[x]) << "," << positionSommet(sommet,n, sommet[y]) << std::endl;
  	}
  	
  	std::cout << std::endl;
  
  //mise a jour des voisins, faire un dessin...

	int Tiz= TriangleArete(i,x,z,T,voisin);
	int Tiw= TriangleArete(i,x,w,T,voisin);
	int Tjz= TriangleArete(j,y,z,T,voisin);
	int Tjw= TriangleArete(j,y,w,T,voisin);
	
	T.at(i).a=z; T.at(i).b=x; T.at(i).c=y;  // mise a jour de Ti et Tj
	T.at(j).a=w; T.at(j).b=x; T.at(j).c=y;

	voisin[i][0]=j; voisin[i][1]=Tiz; voisin[i][2]=Tjz; //mise a jour voisins de i
	voisin[j][0]=i; voisin[j][1]=Tiw; voisin[j][2]=Tjw; //mise a jour voisins de j

	if(Tiw!=-1){//mise a jour voisins Tiw
	
    		if(voisin[Tiw][0]==i){
    			voisin[Tiw][0]=j;
    		}
    		
		if(voisin[Tiw][1]==i){
			voisin[Tiw][1]=j;
		}
		
		if(voisin[Tiw][2]==i){
			voisin[Tiw][2]=j;
		}
	}

	if(Tjz!=-1){//mise a jour voisins Tjz
	
		if(voisin[Tjz][0]==j){
			voisin[Tjz][0]=i;
		}
		
		if(voisin[Tjz][1]==j){
			voisin[Tjz][1]=i;
		}
		
		if(voisin[Tjz][2]==j){
			voisin[Tjz][2]=i;
		}
	}
}

//--------------------------------------------

bool peutFlip(point sommet[], triangle t1, triangle t2) {
      	
	return StrictementDansLeCercleCirconscrit(sommet[t1.a], sommet[t1.b], sommet[t1.c],sommet[TroisiemePoint(t2,t1)]);	
}

//--------------------------------------------


void Delaunay(point* sommet,int n, vector<triangle> &T) {

	bool flag = true;
	
	int voisin[T.size()][3];
	
	for (int i=0; i < T.size(); i++) {
		voisin[i][0] = -1;
		voisin[i][1] = -1;
		voisin[i][2] = -1;
	}
	
	TrianglesVoisins(T.size(),T, voisin);
	
	int k =0;
	int nbFlip = 0;
	while (flag) {
	
		flag = false;
			
		for (int i=0; i < T.size(); i++) {
				
			for (int j =0; j<3; j++) {
				if(voisin[i][j] != -1){
				
					if (peutFlip(sommet, T.at(i), T.at(voisin[i][j])) ) {
									
						Flip(sommet,n, i, voisin[i][j],T, voisin);
						nbFlip++;					
						flag = true;
					}
				}
			}		
		}
		
		k++;
		
		if(k > 10000){
			break;
		}
	}
	
	std::cout << std::endl;
	std::cout <<"Il y a eu " << nbFlip << " flip(s)." << std::endl;
}


/*******************************************************************/
//main
/*******************************************************************/

void AffichageTestCercleCirconscrit(point sommet[4]){

  //Affiche les 4 points de sommet et le cercle circonscrit au trois premiers
  //Pour tester la fonction StrictementDansLeCercleCirconscrit

   ofstream output;
  output.open("Test.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<4;i++){
    output << sommet[i].abscisse << " " << sommet[i].ordonnee << " 2 0 360 arc"
           <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << sommet[i].abscisse+2 << " " << sommet[i].ordonnee << " moveto"
           <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i+1 << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;
  point O;  //Centre du cercle circonscrit
  if(CentreCercleCirconscrit(sommet[0],sommet[1],sommet[2],&O)==1){cout
    << "Points alignes" << endl; exit(1);}
  output << O.abscisse << " " << O.ordonnee << " 2 0 360 arc" <<endl;
  output << "0 setgray" <<endl;
  output << "fill" <<endl;
  output << O.abscisse+2 << " " << O.ordonnee << " moveto" <<endl;
  output << "/Courier findfont 15 scalefont setfont" << endl;
  output << "(O)" << " show" << endl;
  output << "stroke" << endl;
  output << endl;
  int r; //Rayon du cercle circonscrit
     r=(int)sqrt((double)NormeAuCarre(sommet[0],O));
     output << O.abscisse << " " << O.ordonnee << " " << r << " 0 360 arc" <<endl;
     output << "0 setgray" << endl;
     output << "stroke" << endl;
     output << "showpage"<< endl;
     output << endl;
}



int main(){

int n=32;
point sommet[n];

sommet[0].abscisse=100;
sommet[0].ordonnee=100;
sommet[1].abscisse=100;
sommet[1].ordonnee=500;
sommet[2].abscisse=120;
sommet[2].ordonnee=300;
sommet[3].abscisse=140;
sommet[3].ordonnee=100;
sommet[4].abscisse=140;
sommet[4].ordonnee=500;
sommet[5].abscisse=160;
sommet[5].ordonnee=300;
sommet[6].abscisse=180;
sommet[6].ordonnee=100;
sommet[7].abscisse=180;
sommet[7].ordonnee=500;
sommet[8].abscisse=200;
sommet[8].ordonnee=300;
sommet[9].abscisse=220;
sommet[9].ordonnee=100;
sommet[10].abscisse=220;
sommet[10].ordonnee=500;
sommet[11].abscisse=240;
sommet[11].ordonnee=300;
sommet[12].abscisse=260;
sommet[12].ordonnee=100;
sommet[13].abscisse=260;
sommet[13].ordonnee=500;
sommet[14].abscisse=280;
sommet[14].ordonnee=300;
sommet[15].abscisse=300;
sommet[15].ordonnee=100;
sommet[16].abscisse=300;
sommet[16].ordonnee=500;
sommet[17].abscisse=320;
sommet[17].ordonnee=300;
sommet[18].abscisse=340;
sommet[18].ordonnee=100;
sommet[19].abscisse=340;
sommet[19].ordonnee=500;
sommet[20].abscisse=360;
sommet[20].ordonnee=300;
sommet[21].abscisse=380;
sommet[21].ordonnee=100;
sommet[22].abscisse=380;
sommet[22].ordonnee=500;
sommet[23].abscisse=400;
sommet[23].ordonnee=300;
sommet[24].abscisse=420;
sommet[24].ordonnee=100;
sommet[25].abscisse=420;
sommet[25].ordonnee=500;
sommet[26].abscisse=440;
sommet[26].ordonnee=300;
sommet[27].abscisse=460;
sommet[27].ordonnee=100;
sommet[28].abscisse=460;
sommet[28].ordonnee=500;
sommet[29].abscisse=480;
sommet[29].ordonnee=300;
sommet[30].abscisse=500;
sommet[30].ordonnee=100;
sommet[31].abscisse=500;
sommet[31].ordonnee=500;

  int tri[n];
  std::vector<triangle> T;
  
  for(int i=0;i<n;i++){tri[i]=i;}
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);
  AffichageTriangulation(false,n,sommet,t,T);
  
  //Lignes a decommenter, une fois l'implementation realisee

  Delaunay(sommet,n,T);

  AffichageTriangulation(true,n,sommet,t,T);


}

