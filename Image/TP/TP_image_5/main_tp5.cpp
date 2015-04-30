#include "ImageBase.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
ImageBase imIn;
ImageBase* imOut;
int seuil = 20;
int tailleMin = 16;

struct point {
	int x,y;

};

struct node{
    float moyenne;
    float var;
    int x;
    int y;
    int w;
    int h;

    std::vector<int> voisins;
};
std::vector<node *> graphe;

//faire une structure région qui sera enfaite le noeud d'un arbre

void divide(int x, int y, int xmax, int ymax){
    int som = 0;
    int nbPix=0;
    float var = 0 ;
    for (int i = x; i<xmax;i++ ){
            for (int j = y; j < ymax; j++){
                    som += imIn[i][j];
               nbPix++;
            }
    }

   int moyenne = som/nbPix;

   for (int l = x; l<xmax;l++ ){
            for (int k = y; k < ymax; k++){
                    var += pow((imIn[l][k] - moyenne),2);//
            }
    }
    var /= nbPix -1;//var pour toute la région

//printf("region x = %i, y = %i, moyenne = %i ,variance = %f\n",x,y,moyenne,var);

   if (((xmax - x) < tailleMin)||((ymax - y) < tailleMin)||(var < seuil)){
        for (int l = x; l<xmax;l++ ){
            for (int k = y; k < ymax; k++){
               (*imOut)[l][k] = moyenne;
            }
        }

        //remplissage d'un noeud
        node *n = new node(); //(node *)malloc(sizeof(node));
        n->moyenne = moyenne;
        n->var = var;
        n->x = x;
        n->y = y;
        n->w = xmax-x;
        n->h = ymax-y;
        graphe.push_back(n);

    }
   else{

        divide(x,y,x+((xmax-x)/2),y+((ymax-y)/2));//carré en haut à gauche
        divide(x+((xmax-x)/2),y,xmax,y+((ymax-y)/2));//carré en haut à droite
        divide(x,y+((ymax-y)/2),x+((xmax-x)/2),ymax);//carré en bas à gauche
        divide(x+((xmax-x)/2),y+((ymax-y)/2),xmax,ymax);//carré en bas à droite
    }
}

void finalizeGraphe(){
    for(int i = 0; i != graphe.size(); ++i){
        for(int j = i; j != graphe.size(); ++j){
        //printf("%i, %i\n", i, j);
            if(j != i){
                if((graphe[j]->x == (graphe[i]->x+graphe[i]->w)) ||
                    (graphe[j]->y == (graphe[i]->y+graphe[i]->h))){
                    graphe[j]->voisins.push_back(i);
                    graphe[i]->voisins.push_back(j);
                }
            }
        }
    }
}

void fusion(float seuilFusion){
    for(int i = 0; i != graphe.size(); ++i){
        for(int j = 0; j != graphe[i]->voisins.size(); ++j){
            //printf("seuil fusion %i && %i\n", i, graphe[i]->voisins[j]);
            float moyenneSub = abs(graphe[i]->moyenne - graphe[graphe[i]->voisins[j]]->moyenne);
            //printf("semi OK\n");
            if(moyenneSub < seuilFusion){
                //printf("semi OK\n");
                graphe[i]->moyenne = graphe[i]->moyenne + graphe[graphe[i]->voisins[j]]->moyenne;
                graphe[i]->moyenne /= 2.0f;
                graphe[graphe[i]->voisins[j]]->moyenne = graphe[i]->moyenne;
            }
        }
    }
}

void fusion_recolorize(){
    for(int i = 0; i != graphe.size(); ++i){
        for(int j = graphe[i]->y; j != (graphe[i]->y + graphe[i]->h); ++j){
            for(int k = graphe[i]->x; k != (graphe[i]->x + graphe[i]->w); ++k){
                (*imOut)[j][k] = graphe[i]->moyenne;
            }
        }
    }
}

int main(int argc, char **argv) {

	imIn.load("cameraman.pgm");
	printf("imin.width = %i\n",imIn.getWidth());
	imOut = new ImageBase(imIn.getWidth(),imIn.getHeight(),imIn.getColor());
	printf("imout.width = %i\n",imOut->getWidth());
divide(0,0,256,256);
divide(0,256,256,512);
divide(256,0,512,256);
divide(256,256,512,512);

finalizeGraphe();
    printf("finalizeGraphe OK\n");
    fusion(15.f);
    printf("fusion 15.f OK\n");
    fusion_recolorize();

imOut->save("camfus.pgm");

}
