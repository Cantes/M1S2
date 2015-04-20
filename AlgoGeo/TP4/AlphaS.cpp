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

void AffichageTriangulation(int n, point sommet[], int t, triangle T[]){

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
    for(int i=0;i<t;i++){
      output << sommet[T[i].a].abscisse << " " << sommet[T[i].a].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T[i].b].abscisse << " " << sommet[T[i].b].ordonnee
 	    << " lineto"  << endl;
      output << sommet[T[i].b].abscisse << " " << sommet[T[i].b].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T[i].c].abscisse << " " << sommet[T[i].c].ordonnee
 	    << " lineto"  << endl;
      output << sommet[T[i].c].abscisse << " " << sommet[T[i].c].ordonnee 
 	    << " moveto"  << endl;
      output << sommet[T[i].a].abscisse << " " << sommet[T[i].a].ordonnee
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
	
	if(result != 0){
		return false;
	}else{
	
		if( sqrt( pow(A.abscisse - centreCercle.abscisse,2) + pow(A.ordonnee - centreCercle.ordonnee,2) )  
			> 
		    sqrt( pow(D.abscisse - centreCercle.abscisse,2) + pow(D.ordonnee - centreCercle.ordonnee,2) ) ){
			std::cout << "Appartient au cercle " << std::endl;
			return true;
		}else{
			std::cout << "N'appartient pas au cercle" << std::endl;
			return false;
		}
	
	}

}

//----------------------------------------

bool StrictementDansLeCercleCirconscritMemeCote(point A, point B, point C, point D){

  //Renvoie vrai si D est strictement dans le cercle circonscrit de ABC.
  //On suppose C et D du meme cote de (AB).
  //Faire un test entier

 
  //
  // A RECUPERER OU INCLURE
  //

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

int TriangulIncrementale(int n, point* sommet, int* tri, triangle* T){
    
	int j;
	int Kdroite, Kgauche;
	int ind = 0;
	int indEC = 3;
	int* envconv = new int[n+1];
	int indTmp = 1;
	int* envconvTmp = new int[n+1];
	int taille_envconv=3;
	int nbre_triangle=0;  
	
 	triangle T0;
 	T0.a = tri[0];
 	T0.b = tri[1];
 	T0.c = tri[2]; 
 	
 	T[ind] = T0;
 	nbre_triangle++;
 	ind++;
	
 	envconv[0] = T0.c;
 	
 	if( sommet[T0.b].ordonnee > sommet[T0.a].ordonnee){
 	
 		envconv[1] = T0.b; 
 		envconv[2] = T0.a; 
 	}else{
		envconv[1] = T0.a;
		envconv[2] = T0.b; 
 	}

 	envconv[3] = T0.c;
 	
	for(int i=2;i<n-1;i++){

		j = 0;
		
		while(det(sommet[tri[i+1]],sommet[envconv[j]],sommet[tri[i+1]],sommet[envconv[j+1]] ) < 0){		
			
			triangle t;
			t.a = envconv[j];
			t.b = envconv[j+1];
			t.c = tri[i+1];	
			
			T[ind] = t;
			
			nbre_triangle++;
			ind++;
			j++;
		}
		
		Kdroite = j;
		
		j = indEC;
		
		while(det(sommet[tri[i+1]],sommet[envconv[j]],sommet[tri[i+1]],sommet[envconv[j-1]]) > 0){
			
			triangle t;

			t.a = envconv[j];
			t.b = envconv[j-1];
			t.c = tri[i+1];
			
			T[ind] = t;
			
			nbre_triangle++;
			ind++;
			j--;
		
		}
		
		Kgauche = j;
		
		indTmp = 0;
		
		envconvTmp[indTmp] = tri[i+1];
		
		for(int k = Kdroite; k < Kgauche+1; k++){
			indTmp++;
			envconvTmp[indTmp] = envconv[k];
		}
		
		indTmp++;
		envconvTmp[indTmp] = envconvTmp[0];

		indEC = indTmp ;
		
		for(int k = 0; k<indEC+1; k++){
			envconv[k] = envconvTmp[k];
				
		}
 	}

  return nbre_triangle;

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

void TrianglesVoisins(int t, triangle T[], int voisin[][3]){
 
  //Calcul pour chaque triangle les indices des triangles qui lui sont adjacents

  for(int i=0;i<t;i++){
    for(int j=0;j<i;j++){
      if(TrianglesAdjacents(T[i],T[j])){
	int case_libre;
	if(voisin[i][0]==-1){case_libre=0;}
	   else{if(voisin[i][1]==-1){case_libre=1;}
	   else{case_libre=2;}}
	voisin[i][case_libre]=j;
	if(voisin[j][0]==-1){case_libre=0;}
	else{if(voisin[j][1]==-1){case_libre=1;}
	else{case_libre=2;}}
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

void Flip(int i, int j, int t, triangle T[], int voisin[][3]){

  //Effectue un 'flip' entre les triangles T[i] et T[j]
  //t est la taille du tableau T et voisin, tableau calcule
  //par la fonction TrianglesVoisins, sera mis-a-jour

  int vieux_voisins_Ti[3]={voisin[i][0],voisin[i][1],voisin[i][2]};
  int vieux_voisins_Tj[3]={voisin[j][0],voisin[j][1],voisin[j][2]};
  int x=TroisiemePoint(T[i],T[j]);// On nomme les 4 sommets
  int y=TroisiemePoint(T[j],T[i]);
  int z;
  int w;
  if(T[i].a==x){z=T[i].b; w=T[i].c;}
  if(T[i].b==x){z=T[i].a; w=T[i].c;}
  if(T[i].c==x){z=T[i].a; w=T[i].b;}
  T[i].a=z;T[i].b=x;T[i].c=y;  // mise a jour de Ti et Tj
  T[j].a=w;T[j].b=x;T[j].c=y;
  //mise a jour des voisins: A faire plus proprement...
 for(int i=0;i<t;i++){
    voisin[i][0]=-1;
    voisin[i][1]=-1;
    voisin[i][2]=-1;
  }
  TrianglesVoisins(t,T,voisin);
 
}

//--------------------------------------------

bool peutFlip(point sommet[], triangle t1, triangle t2) {

	std::vector<int> listePointT1;
	
	listePointT1.push_back(t1.a);
	listePointT1.push_back(t1.b);
	listePointT1.push_back(t1.c);

	std::vector<int> listePointT2;
	
	listePointT2.push_back(t2.a);
	listePointT2.push_back(t2.b);
	listePointT2.push_back(t2.c);
	
	for (int i = 0; i<listePointT1.size(); i++) {
		for(int j = 0; j<listePointT2.size(); j++){
			if( listePointT2.at(j) == listePointT1.at(i)){
				listePointT2.erase(listePointT2.begin() + j);
			}
		
		}
	}
	
	if (listePointT2.size() != 1) {
		return false;
	}
	
	int pointA = listePointT1.at(0);
	int pointB = listePointT1.at(1);
	int pointC = listePointT1.at(2);
	int pointD = listePointT2.at(0);
	
	point centreCercle;
	
	CentreCercleCirconscrit(sommet[pointA], sommet[pointB], sommet[pointC], &centreCercle);
	
	return (  sqrt( pow( sommet[pointA].abscisse - centreCercle.abscisse ,2) + pow( sommet[pointA].ordonnee - centreCercle.ordonnee ,2)) 
			>  
		  sqrt( pow( sommet[pointD].abscisse - centreCercle.abscisse ,2) + pow( sommet[pointD].ordonnee - centreCercle.ordonnee ,2))
	       );

}

//--------------------------------------------

void Delaunay(int n, point sommet[],int t, triangle T[]){

	bool flag=true;
	int voisin[t][3];
	
	TrianglesVoisins(t,T, voisin);

	while(flag){
  		flag = false;
  		
		for (int i =0; i< t; i++) {
			for (int j = 0; j<t; j++) {
				if(peutFlip(sommet, T[i], T[j])){
					Flip(i, j, t, T, voisin);
					flag = true;
				}
			}
		}
  
	}
	
	std::cout << "Fin de Delaunay" << std::endl;
}

/*******************************************************************/
//main
/*******************************************************************/


int main(){

  int n=200; 

  point sommet[200]={
    {416,529},{505,438},{268,188},{188,276},{312,595},{542,411},{331,195},{483,331},{427,216},{260,241},
    {137,456},{291,236},{412,291},{430,617},{192,342},{308,241},{460,265},{355,232},{537,326},{556,288},
    {251,264},{537,260},{195,443},{382,596},{404,224},{542,321},{166,516},{472,256},{417,177},{411,505},
    {404,166},{494,595},{502,353},{251,481},{558,467},{561,361},{480,561},{147,387},{404,248},{227,201},
    {241,532},{251,472},{360,249},{552,390},{171,267},{491,502},{329,520},{168,328},{451,232},{584,446},
    {345,540},{121,380},{256,307},{217,249},{435,560},{508,460},{128,464},{451,500},{363,227},{585,428},
    {192,404},{152,518},{489,536},{473,500},{275,294},{459,488},{540,414},{140,364},{140,380},{350,609},
    {528,433},{267,539},{422,521},{160,248},{464,518},{339,529},{472,513},{219,403},{427,288},{262,576},
    {344,604},{204,320},{441,204},{281,630},{516,276},{486,379},{220,508},{510,513},{465,540},{196,454},
    {260,254},{540,536},{230,280},{470,329},{313,576},{406,209},{488,425},{411,268},{488,420},{444,264},
    {168,491},{427,225},{312,606},{564,411},{160,438},{212,454},{531,249},{145,360},{459,310},{225,294},
    {243,539},{249,246},{556,342},{564,332},{433,494},{313,584},{483,547},{374,235},{505,257},{265,243},
    {432,624},{412,228},{278,294},{456,304},{212,286},{513,300},{545,380},{222,553},{208,398},{560,464},
    {401,192},{262,580},{350,568},{233,281},{331,198},{233,481},{220,564},{395,224},{328,182},{137,355},
    {512,342},{510,326},{236,248},{454,248},{459,545},{152,409},{425,174},{428,617},{524,468},{454,472},
    {116,379},{515,326},{352,537},{216,464},{436,179},{192,524},{424,612},{355,203},{476,366},{460,316},
    {158,545},{166,406},{486,587},{198,214},{188,355},{446,190},{248,515},{528,521},{332,561},{550,473},
    {227,609},{366,523},{204,262},{153,443},{371,544},{524,296},{459,614},{137,374},{465,356},{492,222},
    {288,614},{347,265},{486,518},{361,217},{518,446},{180,305},{315,172},{329,201},{241,614},{198,368},
    {556,316},{252,622},{212,264},{353,280},{204,267},{185,300},{515,342},{344,571},{155,513},{494,289},
  };



  int tri[n];
  triangle T[2*n];
  for(int i=0;i<n;i++){tri[i]=i;}
 
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);

  Delaunay(n,sommet,t,T);

  float rayon[t];//tableau contenant les rayons
  for(int i=0;i<t;i++){
    rayon[i]=RayonCercleCirconscrit(sommet[T[i].a],sommet[T[i].b],sommet[T[i].c]);
  }
  AffichageTriangulation(n,sommet,t,T);//affichage de Delaunay



//seuillage:

  triangle Taccepte[2*n];//les triangles qu'on affichera
  float alpha;  

while(1){
  cout << "Valeur de alpha: ";
  cin >> alpha;
  int t_acceptes=0;
  int indice=0;
  for(int i=0;i<t;i++){
    if(rayon[i]<alpha){//on accepte le triangle i
      t_acceptes++;
      Taccepte[indice].a=T[i].a; 
      Taccepte[indice].b=T[i].b; 
      Taccepte[indice].c=T[i].c;
      indice++;
    }
  }
  AffichageTriangulation(n,sommet,t_acceptes,Taccepte);
 }
}
