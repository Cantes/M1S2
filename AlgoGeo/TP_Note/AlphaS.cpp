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

int Carre(int x){
  return x*x;}

//-----------------------------

int NormeAuCarre(point p1,point p2){

  //Calcul la norme au carre de p1p2

  return Carre(p1.ordonnee-p2.ordonnee)+Carre(p1.abscisse-p2.abscisse);
}

//------------------------------------------------------------------------


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

//-----------------------------

float RayonCercleCirconscrit(point A, point B, point C){
  //Renvoie le rayon du cercle circonscrit a ABC
  
	point centreCercle;
  
	CentreCercleCirconscrit(A,B,C, &centreCercle);
   
	return sqrt( pow( A.abscisse - centreCercle.abscisse ,2) + pow( A.ordonnee - centreCercle.ordonnee ,2)); 

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

  //Affichage de n points dont les coordonnees sont dans sommet[n][2]
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

void AffichageTriangulation(int n, point sommet[], std::vector<triangle> T){

  //Affichage des n points du plan dont les coordonnees sont dans sommet[][2] et d'une triangulation
  //en t triangles stockes dans T, tableau de taille t.

   ofstream output;
   output.open("AlphaShape.ps");
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i].abscisse << " " << sommet[i].ordonnee << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
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

void AffichageTriangulationDelauIncre(bool delo, int n, point sommet[], int t, std::vector<triangle> T){

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
//Reperer un point par rapport au cercle circonscrit a un triangle
/*******************************************************************/

bool MemeCote(point A, point B, point C, point D){

  //Renvoie vrai si C et D sont du meme cote de (AB).

  if((det(A,B,A,C)*det(A,B,A,D))>0){return true;}
  else{  return false;}
}

//---------------------------------------

bool StrictementDansLeCercleCirconscrit(point A, point B, point C, point D){

	int result;
	point centreCercle;
	
	result = CentreCercleCirconscrit(A, B,C,&centreCercle);
	
	if(result == 1){
		return false;
	}else{
		return (sqrt( pow(A.abscisse - centreCercle.abscisse,2) + pow(A.ordonnee - centreCercle.ordonnee,2) )
			> 
		    sqrt( pow(D.abscisse - centreCercle.abscisse,2) + pow(D.ordonnee - centreCercle.ordonnee,2) ) );

	
	}

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
		
		while(det(sommet[tri[i+1]],sommet[envconv.at(j)],sommet[tri[i+1]],sommet[envconv.at(j+1)] ) <= 0){		
			
			triangle t;
			t.a = envconv.at(j);
			t.b = envconv.at(j+1);
			t.c = tri[i+1];	
			
			T.push_back(t);

			j++;
		}
		
		Kdroite = j;
		
		j = envconv.size()-1;
		
		while(det(sommet[tri[i+1]],sommet[envconv.at(j)],sommet[tri[i+1]],sommet[envconv.at(j-1)]) >= 0){
			
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

//---------------------------------------------

void Flip(int i, int j, std::vector<triangle> &T, int voisin[][3]){

  //Effectue un 'flip' entre les triangles T[i] et T[j]
  //t est la taille du tableau T et voisin, tableau calcule
  //par la fonction TrianglesVoisins, sera mis-a-jour

  int vieux_voisins_Ti[3]={voisin[i][0],voisin[i][1],voisin[i][2]};
  int vieux_voisins_Tj[3]={voisin[j][0],voisin[j][1],voisin[j][2]};
  int x=TroisiemePoint(T.at(i),T.at(j));// On nomme les 4 sommets
  int y=TroisiemePoint(T.at(j),T.at(i));
  int z;
  int w;
  if(T.at(i).a==x){z=T.at(i).b; w=T.at(i).c;}
  if(T.at(i).b==x){z=T.at(i).a; w=T.at(i).c;}
  if(T.at(i).c==x){z=T.at(i).a; w=T.at(i).b;}
 

  //mise a jour des voisins, faire un dessin...

  int Tiz= TriangleArete(i,x,z,T,voisin);
  int Tiw= TriangleArete(i,x,w,T,voisin);
  int Tjz= TriangleArete(j,y,z,T,voisin);
  int Tjw= TriangleArete(j,y,w,T,voisin);

  T.at(i).a=z;T.at(i).b=x;T.at(i).c=y;  // mise a jour de Ti et Tj
  T.at(j).a=w;T.at(j).b=x;T.at(j).c=y;

  voisin[i][0]=j; voisin[i][1]=Tiz; voisin[i][2]=Tjz; //mise a jour voisins de i
  voisin[j][0]=i; voisin[j][1]=Tiw; voisin[j][2]=Tjw; //mise a jour voisins de j

  if(Tiw!=-1){//mise a jour voisins Tiw
    if(voisin[Tiw][0]==i){voisin[Tiw][0]=j;}
    if(voisin[Tiw][1]==i){voisin[Tiw][1]=j;}
    if(voisin[Tiw][2]==i){voisin[Tiw][2]=j;}
  }

  if(Tjz!=-1){//mise a jour voisins Tjz
    if(voisin[Tjz][0]==j){voisin[Tjz][0]=i;}
    if(voisin[Tjz][1]==j){voisin[Tjz][1]=i;}
    if(voisin[Tjz][2]==j){voisin[Tjz][2]=i;}
  }
  
  
}

//--------------------------------------------

bool peutFlip(point sommet[], triangle t1, triangle t2) {
	
	return StrictementDansLeCercleCirconscrit(sommet[t1.a], sommet[t1.b], sommet[t1.c],sommet[TroisiemePoint(t2,t1)]);
	
}

//--------------------------------------------

void Delaunay(point* sommet, vector<triangle> &T) {

	bool flag = true;
	
	int voisin[T.size()][3];
	
	for (int i=0; i < T.size(); i++) {
		voisin[i][0] = -1;
		voisin[i][1] = -1;
		voisin[i][2] = -1;
	}
	
	TrianglesVoisins(T.size(),T, voisin);
	
	int k = 0;
	
	while (flag) {
		flag = false;
			
		for (int i=0; i < T.size(); i++) {
				
			for (int j =0; j<3; j++) {
				if(voisin[i][j] != -1){
					if (peutFlip(sommet, T.at(i), T.at(voisin[i][j])) ) {
									
						Flip(i, voisin[i][j],T, voisin);
											
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
}
//*****************************************************************************


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



/*******************************************************************/
//main
/*******************************************************************/


int main(){

int n=500;

point sommet[500]={
{225,422},{177,491},{257,395},{217,575},{425,272},{332,197},{297,638},{277,647},{285,347},{307,665},
{62,185},{275,239},{242,359},{285,185},{220,371},{165,257},{247,329},{227,179},{312,584},{267,206},
{227,149},{310,626},{265,314},{225,518},{350,215},{232,716},{127,185},{232,533},{122,221},{305,266},
{207,617},{167,245},{305,185},{267,191},{242,476},{235,485},{202,122},{195,551},{270,644},{375,212},
{275,485},{535,245},{145,146},{295,242},{210,719},{262,404},{300,563},{167,623},{200,680},{260,647},
{102,191},{525,176},{242,581},{215,674},{165,161},{220,134},{267,332},{387,185},{285,182},{257,311},
{225,155},{235,389},{252,275},{95,209},{212,683},{77,176},{282,299},{192,233},{162,560},{70,230},
{257,662},{160,152},{245,749},{255,296},{245,734},{252,692},{150,575},{240,641},{325,272},{367,317},
{195,425},{400,191},{550,233},{340,215},{232,641},{287,245},{225,689},{447,182},{262,377},{190,638},
{387,305},{150,563},{292,536},{345,320},{260,458},{445,152},{240,368},{282,683},{172,122},{247,437},
{250,239},{330,356},{402,281},{227,497},{270,182},{525,212},{200,152},{60,197},{110,215},{445,272},
{280,740},{287,695},{230,281},{280,254},{292,680},{230,242},{212,155},{240,422},{192,659},{145,266},
{162,245},{285,500},{422,164},{150,293},{187,239},{145,290},{435,272},{182,161},{167,572},{177,647},
{182,476},{270,632},{517,230},{477,152},{132,272},{305,215},{125,281},{167,275},{110,140},{515,176},
{302,176},{190,488},{292,503},{225,272},{150,278},{215,701},{257,425},{207,284},{220,128},{102,161},
{250,257},{510,209},{190,584},{260,545},{305,665},{387,173},{242,230},{110,140},{240,647},{175,530},
{290,209},{287,332},{262,302},{265,371},{330,227},{182,443},{287,182},{242,395},{275,560},{407,272},
{252,542},{225,371},{185,137},{427,269},{187,470},{532,188},{227,191},{377,224},{170,668},{155,578},
{317,239},{180,461},{297,239},{272,431},{225,515},{242,659},{152,569},{280,521},{175,551},{240,365},
{287,656},{517,233},{137,269},{120,221},{245,248},{425,284},{302,671},{197,539},{270,608},{260,191},
{162,524},{252,236},{412,191},{237,635},{285,533},{267,191},{452,263},{167,263},{80,152},{270,239},
{217,377},{167,656},{192,254},{205,155},{277,731},{492,191},{250,689},{250,335},{475,185},{162,560},
{545,224},{162,539},{270,203},{242,584},{510,167},{167,479},{252,590},{172,605},{487,257},{230,710},
{177,662},{377,311},{262,365},{117,227},{237,281},{165,665},{137,251},{165,140},{390,179},{142,134},
{380,230},{260,527},{445,176},{195,584},{235,647},{472,179},{92,167},{237,599},{190,665},{230,719},
{222,170},{200,659},{215,665},{270,164},{270,647},{222,272},{462,170},{100,287},{527,236},{405,272},
{265,740},{287,347},{165,233},{242,230},{515,239},{230,470},{245,263},{250,452},{505,227},{122,287},
{282,290},{275,551},{202,116},{222,176},{125,161},{380,296},{137,116},{115,176},{232,635},{207,707},
{215,491},{202,623},{292,323},{390,290},{252,293},{172,494},{212,434},{242,206},{325,203},{110,242},
{217,491},{222,647},{485,161},{282,464},{510,221},{522,218},{270,533},{172,518},{355,233},{140,140},
{207,674},{290,608},{495,191},{192,503},{212,119},{492,263},{227,167},{190,548},{285,188},{490,152},
{515,173},{265,662},{237,392},{270,368},{205,689},{330,335},{192,656},{265,617},{395,176},{225,653},
{307,278},{467,194},{100,248},{155,575},{200,152},{210,479},{247,140},{177,593},{260,449},{270,692},
{227,566},{82,179},{247,245},{345,230},{312,656},{222,569},{60,209},{202,149},{372,224},{360,218},
{277,170},{177,134},{280,326},{107,146},{302,659},{232,734},{227,512},{270,674},{252,254},{245,599},
{350,197},{195,644},{282,260},{95,266},{222,716},{102,287},{397,212},{245,191},{302,233},{95,170},
{252,581},{285,482},{262,143},{280,155},{150,143},{87,200},{282,227},{367,233},{230,419},{257,389},
{182,116},{480,155},{180,560},{137,296},{365,212},{180,242},{117,293},{215,674},{215,707},{152,533},
{250,419},{240,236},{262,512},{255,704},{47,215},{275,608},{267,284},{242,449},{227,638},{115,263},
{245,173},{255,698},{507,188},{395,179},{100,221},{212,704},{132,257},{262,455},{205,626},{377,296},
{217,458},{177,497},{217,722},{297,239},{245,494},{162,275},{502,170},{100,182},{245,437},{202,620},
{230,353},{537,197},{177,560},{557,206},{467,173},{482,152},{220,638},{260,230},{305,332},{432,257},
{157,140},{95,155},{310,329},{195,569},{300,239},{150,131},{345,200},{255,704},{310,230},{217,599},
{227,608},{275,335},{270,629},{212,575},{152,560},{232,647},{152,125},{490,167},{210,563},{77,230},
{337,218},{507,230},{427,200},{450,197},{220,701},{237,413},{240,557},{87,203},{465,251},{230,614},
{72,257},{510,212},{67,179},{162,167},{517,161},{507,239},{135,119},{222,158},{247,503},{255,737},
{285,590},{380,299},{292,167},{220,593},{425,161},{247,575},{162,626},{430,278},{240,461},{252,599},
{310,584},{300,317},{230,668},{230,665},{290,656},{400,221},{360,314},{215,446},{222,125},{505,185},
{212,530},{180,479},{277,371},{162,527},{542,209},{302,584},{505,257},{540,197},{180,161},{290,227},
{450,254},{247,563},{325,290},{195,494},{400,293},{265,449},{250,623},{237,731},{227,377},{210,581},
};


	int tri[n];
	std::vector<triangle> T;
	
	for(int i=0;i<n;i++){
		tri[i]=i;
	}
	
	AffichagePoints(n,sommet);
	TriLexicographique(n,sommet,n,tri);
	int t=TriangulIncrementale(n,sommet,tri,T);
	
	AffichageTriangulationDelauIncre(false,n,sommet,t,T);

	Delaunay(sommet,T);
	
	AffichageTriangulationDelauIncre(true,n,sommet,t,T);
		
	float rayon[T.size()];//tableau contenant les rayons
	
	for(int i=0;i<T.size();i++){
		rayon[i]=RayonCercleCirconscrit(sommet[T[i].a],sommet[T[i].b],sommet[T[i].c]);
	}
	  
	//seuillage:

	std::vector<triangle> Taccepte;//les triangles qu'on affichera
	float alpha;  

	while(1){
		cout << "Valeur de alpha: ";
		cin >> alpha;
		
		for(int i=0;i<T.size();i++){
		
			if(rayon[i]<alpha){//on accepte le triangle i
				Taccepte.push_back(T.at(i));
			}
		}
		
		AffichageTriangulation(n,sommet,Taccepte);
	}
}
