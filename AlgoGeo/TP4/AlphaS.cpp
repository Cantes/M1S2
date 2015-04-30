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

int n=800;


point sommet[800]={
{417,688},{163,321},{425,462},{411,691},{196,552},{334,433},{200,334},{312,392},{552,624},{262,537},
{328,566},{416,520},{163,452},{401,475},{432,604},{278,598},{163,444},{59,353},{158,326},{360,408},
{321,462},{272,606},{115,668},{243,462},{297,515},{304,670},{78,353},{270,568},{323,536},{419,688},
{526,612},{457,524},{190,424},{59,387},{384,428},{156,667},{408,550},{176,368},{302,571},{198,484},
{128,396},{168,494},{220,427},{347,608},{395,646},{408,600},{326,672},{235,636},{204,496},{136,710},
{481,680},{166,657},{134,377},{211,694},{488,699},{172,526},{497,632},{283,428},{107,681},{454,590},
{531,632},{433,548},{187,648},{555,641},{361,598},{353,478},{320,544},{268,547},{456,707},{409,584},
{352,566},{49,457},{148,478},{49,465},{504,712},{172,713},{233,321},{267,427},{499,593},{478,712},
{233,456},{150,710},{262,600},{329,627},{118,708},{356,472},{145,715},{281,665},{158,499},{238,572},
{496,646},{54,478},{155,664},{243,641},{116,396},{518,622},{104,488},{148,718},{163,323},{556,696},
{96,377},{401,508},{240,400},{528,676},{179,364},{308,480},{44,382},{504,590},{115,694},{331,392},
{123,404},{414,584},{409,665},{212,664},{307,523},{356,635},{328,507},{281,387},{331,675},{334,526},
{177,312},{257,489},{353,566},{560,662},{84,464},{233,441},{315,464},{504,716},{368,606},{128,529},
{344,451},{486,710},{432,552},{422,633},{368,654},{163,347},{292,404},{246,308},{468,694},{403,595},
{334,534},{313,480},{582,664},{372,646},{430,636},{80,390},{177,500},{180,680},{316,683},{456,718},
{148,484},{206,451},{308,553},{56,468},{230,520},{235,632},{275,600},{206,520},{204,462},{288,380},
{467,683},{273,462},{430,491},{211,681},{278,571},{441,667},{219,475},{177,534},{153,515},{504,593},
{323,592},{236,652},{452,510},{62,476},{324,550},{161,720},{281,435},{353,633},{243,644},{140,448},
{260,619},{230,612},{104,704},{563,718},{28,457},{185,691},{268,553},{164,460},{566,715},{219,395},
{475,545},{46,366},{113,369},{401,659},{372,675},{467,600},{321,532},{318,529},{244,508},{193,699},
{366,489},{124,692},{276,659},{308,592},{459,537},{291,496},{352,521},{480,731},{563,667},{206,454},
{236,366},{414,584},{257,476},{270,649},{260,662},{550,665},{185,675},{192,422},{272,596},{174,433},
{278,430},{288,657},{324,676},{276,606},{222,665},{246,641},{390,492},{353,620},{276,457},{131,411},
{385,424},{406,558},{267,627},{417,449},{592,651},{416,646},{222,508},{248,313},{520,649},{217,433},
{174,550},{320,614},{318,577},{403,672},{267,376},{268,409},{65,499},{270,488},{280,476},{288,681},
{300,441},{518,710},{193,675},{324,526},{214,390},{318,436},{355,632},{472,510},{238,379},{275,675},
{153,345},{211,457},{307,364},{153,428},{212,465},{392,513},{315,449},{401,590},{78,374},{416,678},
{131,668},{508,619},{220,494},{436,566},{246,609},{249,659},{211,672},{288,561},{246,502},{246,585},
{73,488},{312,675},{411,672},{195,688},{299,380},{81,376},{185,507},{313,507},{265,598},{211,419},
{332,470},{451,651},{214,659},{262,577},{473,595},{163,321},{137,668},{217,539},{75,388},{313,641},
{107,704},{436,681},{280,576},{382,510},{420,585},{441,568},{305,556},{64,348},{192,449},{300,395},
{267,318},{281,536},{174,358},{304,387},{334,681},{371,601},{398,672},{225,492},{299,406},{401,582},
{315,539},{260,486},{204,457},{28,449},{390,630},{188,649},{132,488},{526,667},{350,424},{468,689},
{363,531},{552,726},{244,652},{443,681},{404,641},{305,580},{187,340},{352,577},{446,513},{145,393},
{48,358},{323,531},{89,497},{227,390},{236,467},{224,660},{336,552},{489,627},{425,499},{385,568},
{217,664},{217,686},{396,604},{280,481},{156,412},{529,622},{262,372},{329,641},{299,524},{150,488},
{561,710},{444,536},{115,699},{233,672},{302,678},{472,731},{227,481},{355,456},{390,644},{243,686},
{484,553},{46,452},{387,646},{291,446},{182,430},{51,377},{406,689},{80,464},{225,675},{20,481},
{430,500},{204,339},{161,334},{244,660},{288,454},{340,556},{172,656},{387,656},{476,624},{139,401},
{448,520},{86,513},{200,329},{435,662},{92,398},{227,401},{57,393},{526,680},{390,534},{334,571},
{513,627},{177,715},{72,342},{192,683},{457,571},{68,352},{192,555},{446,705},{163,408},{393,512},
{540,716},{264,660},{262,534},{209,468},{424,569},{486,564},{542,670},{152,480},{284,489},{312,614},
{396,507},{105,369},{129,489},{422,689},{248,462},{228,484},{438,561},{43,467},{310,512},{67,464},
{91,510},{232,465},{201,686},{241,630},{270,409},{264,648},{486,633},{241,612},{436,593},{264,552},
{312,364},{499,668},{267,598},{377,544},{380,630},{280,372},{427,523},{57,460},{187,555},{248,403},
{288,348},{571,657},{244,665},{353,572},{388,667},{121,396},{417,536},{347,515},{190,440},{192,478},
{299,611},{448,587},{348,548},{547,737},{187,473},{275,502},{174,504},{236,368},{304,569},{78,358},
{139,681},{171,518},{238,529},{235,424},{454,699},{152,448},{131,395},{280,577},{379,662},{195,440},
{81,454},{318,380},{206,388},{550,643},{307,452},{238,518},{251,465},{230,433},{547,624},{284,622},
{100,468},{347,419},{243,587},{510,620},{252,566},{329,436},{132,403},{268,382},{513,603},{340,556},
{297,460},{206,385},{385,622},{516,708},{430,548},{265,403},{222,364},{409,628},{184,451},{270,524},
{129,409},{209,416},{222,456},{491,724},{374,433},{372,531},{59,392},{267,552},{280,576},{211,404},
{414,582},{366,500},{96,411},{96,494},{241,409},{491,737},{233,491},{345,590},{585,638},{403,483},
{257,600},{179,342},{388,545},{428,576},{241,344},{337,473},{275,412},{278,398},{353,572},{211,472},
{312,665},{427,534},{464,497},{360,654},{452,598},{318,368},{193,379},{192,662},{233,401},{150,484},
{102,515},{160,438},{446,492},{489,630},{396,662},{369,579},{52,481},{385,624},{355,528},{145,513},
{307,449},{241,686},{404,497},{238,512},{555,708},{475,640},{296,388},{265,569},{384,547},{302,558},
{280,371},{289,622},{280,667},{529,726},{510,641},{376,627},{356,548},{302,646},{585,660},{588,648},
{227,497},{371,587},{260,643},{417,545},{422,545},{372,536},{67,459},{233,617},{84,380},{331,409},
{212,651},{284,491},{161,353},{348,508},{102,692},{425,680},{48,454},{460,694},{459,713},{166,707},
{384,564},{353,598},{252,491},{232,440},{340,401},{171,406},{216,353},{219,635},{203,649},{182,542},
{48,486},{332,651},{406,467},{398,588},{259,366},{454,632},{497,635},{224,497},{19,465},{129,672},
{204,452},{329,516},{460,579},{228,420},{457,619},{196,689},{267,344},{451,521},{96,387},{252,630},
{204,467},{318,566},{304,564},{187,427},{267,576},{48,464},{358,638},{432,577},{187,500},{102,372},
{203,462},{262,473},{406,574},{275,593},{348,636},{57,465},{272,401},{363,507},{438,569},{484,742},
{78,500},{454,670},{344,612},{304,480},{289,416},{129,473},{260,502},{268,350},{523,726},{230,412},
{476,625},{230,611},{382,494},{187,339},{214,584},{456,713},{83,400},{312,483},{140,699},{214,560},
{412,628},{164,489},{262,632},{188,540},{200,574},{446,508},{185,379},{204,686},{67,371},{177,412},
{508,707},{508,625},{265,446},{220,403},{368,633},{392,449},{192,336},{563,718},{228,528},{180,441},
{435,476},{419,688},{270,555},{83,452},{416,452},{126,492},{217,372},{268,675},{369,516},{238,604},
{212,539},{315,644},{443,628},{278,561},{409,656},{563,700},{323,419},{515,656},{451,571},{408,476},
{460,496},{571,668},{150,668},{233,393},{350,512},{193,328},{507,740},{316,576},{256,534},{440,563},
{547,612},{224,416},{523,659},{257,470},{376,489},{444,540},{204,440},{251,619},{105,393},{164,536},
{257,571},{296,400},{16,465},{262,579},{152,681},{201,459},{331,494},{35,444},{313,369},{328,601},
{312,449},{364,640},{152,715},{355,484},{385,468},{328,667},{148,332},{32,486},{326,531},{364,443},
{291,513},{128,500},{336,483},{512,612},{308,545},{40,460},{232,684},{371,462},{310,630},{76,398},
{209,401},{228,432},{483,571},{257,652},{529,680},{395,576},{496,688},{252,632},{444,689},{211,515},
{449,696},{286,614},{457,499},{233,315},{200,656},{395,539},{366,425},{356,512},{428,643},{451,547},
{584,696},{534,641},{542,739},{264,592},{360,590},{52,347},{131,657},{310,540},{363,656},{406,454},
{209,384},{280,590},{404,520},{548,729},{208,398},{534,648},{452,585},{356,454},{259,486},{366,510},
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
