#include <iostream>
#include <fstream>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265
#include <stdlib.h>


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

void AffichageTriangulation(bool delo, int n, point sommet[], int t, triangle T[]){

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
//Generation de sommets au hasard
/*******************************************************************/

void PointAuHasard(int n,point sommet[]){

  //Tire n points au hasard uniformement repartis dans un disque, leurs coordonnees sont
  //stockees dans sommet[]
  int graine=time(NULL);
  cout << "graine: "<< graine << endl;
  srand(graine);
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

bool StrictementDansLeCercleCirconscrit(point A, point B, point C, point D){

  //Renvoie vrai si D est strictement dans le cercle circonscrit de ABC, quelquesoit sa position.

  //
  //A COMPLETER
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


int TriangulIncrementale(int n, point sommet[], int tri[], triangle T[]){
 

  //
  // REPRENDRE LE CODE DE LA FONCTION DE L EXERCICE 1
  //

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

int TriangleArete(int i, int x, int y, triangle T[], int voisin[][3]){

  //Renvoie le second triangle de T ayant xy comme arete (T[i] etant le premier)

  for(int k=0;k<3;k++){
    if(voisin[i][k]==-1){continue;}//on tape de l'autre cote de l'enveloppe convexe
    if((T[voisin[i][k]].a == x) && ((T[voisin[i][k]].b == y) || (T[voisin[i][k]].c == y))){
      return voisin[i][k];}
    if((T[voisin[i][k]].b == x) && ((T[voisin[i][k]].a == y) || (T[voisin[i][k]].c == y))){
      return voisin[i][k];}
    if((T[voisin[i][k]].c == x) && ((T[voisin[i][k]].b == y) || (T[voisin[i][k]].a == y))){
      return voisin[i][k];}
  }
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
 

  //mise a jour des voisins, faire un dessin...

  int Tiz= TriangleArete(i,x,z,T,voisin);
  int Tiw= TriangleArete(i,x,w,T,voisin);
  int Tjz= TriangleArete(j,y,z,T,voisin);
  int Tjw= TriangleArete(j,y,w,T,voisin);

  T[i].a=z;T[i].b=x;T[i].c=y;  // mise a jour de Ti et Tj
  T[j].a=w;T[j].b=x;T[j].c=y;

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

int Delaunay(int n, point sommet[],int t, triangle T[]){
  int flag=1;
  int voisin[t][3]; // Creation et initialisation de voisin
  for(int i=0;i<t;i++){
    voisin[i][0]=-1;
    voisin[i][1]=-1;
    voisin[i][2]=-1;
  }
  TrianglesVoisins(t,T,voisin);

  
  //
  //A COMPLETER
  //


    return 0;
}

/*******************************************************************/
//main
/*******************************************************************/


int main(){
 
  int n=1000;

  point sommet[n];
  int tri[n];
  triangle T[2*n];
  for(int i=0;i<n;i++){tri[i]=i;}
  PointAuHasard(n,sommet);
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);
  AffichageTriangulation(false,n,sommet,t,T);
  
  //Lignes a decommenter, une fois l'implementation realisee

  //Delaunay(n,sommet,t,T);
  //AffichageTriangulation(true,n,sommet,t,T); Delaunay(n,sommet,t,T);


}

