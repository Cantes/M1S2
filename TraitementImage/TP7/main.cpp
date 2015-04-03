#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "image_ppm.h"

using namespace std;

int moyenneImage(char* nomImage){

	int moy = 0;
	OCTET *ImgIn;
	int nH, nW, nTaille;
		
	lire_nb_lignes_colonnes_image_pgm(nomImage, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(nomImage, ImgIn, nH * nW);
	
	for(int i=0; i<nH; i++){
		for(int j=0; j<nW; j++){
			moy += ImgIn[i*nW+j];
		}	
	}

	return (moy/nTaille);

}

int moyenneImagette(OCTET* imagette, int x, int y, int nW){
	int moy = 0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8;j++){
			moy += imagette[(x+i)*nW+(y+j)];
		}
	}
	return ( moy / 64);
}

OCTET* divisionImage(char* nomImage, char* imageSortie){

	OCTET *ImgIn, *ImgOut;
	int nH, nW, nTaille;
		
	lire_nb_lignes_colonnes_image_pgm(nomImage, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(nomImage, ImgIn, nH * nW);
		
	allocation_tableau(ImgOut, OCTET,  nTaille);
	
	
	for(int i=0; i<nH; i = i+8){
	
		for(int j=0; j<nW; j = j+8){
		
			int moy = moyenneImagette(ImgIn, i, j, nW);
			
			for(int k=i; k< (i+8); k++){
				for(int l=j; l< (j+8); l++){
					ImgOut[k*nW+l] = moy;
				}
			}
		}	
	}
		
	return ImgOut;
}

int* getTableauMoyenneImage(int nbImage){

	int* tab = new int[nbImage];

	char* chemin = new char[256];
	char* fichier = new char[256];
	char* fin = new char[256];
	
	chemin = "Images/";
	fin = ".pgm";
	
	FILE* fichierSortie;
	fichierSortie = fopen("moyenneTableau.txt", "wab");
	
        for(int i=0; i<nbImage; i++){
        	
		char result[100];   
		std::string s = std::to_string(i);
		char const *pchar = s.c_str();
		
		strcpy(result,chemin); 
		strcat(result,pchar);
		strcat(result,fin);  

		tab[i] = moyenneImage(result);
		fprintf(fichierSortie, "%d \n",tab[i]);			
	}
 
	return tab;
}

OCTET* redimension(char* nomImage){

	OCTET *ImgIn, *ImgOut;
	int nH, nW, nTaille;
		
	lire_nb_lignes_colonnes_image_pgm(nomImage, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(nomImage, ImgIn, nH * nW);
		
	allocation_tableau(ImgOut, OCTET,  8*8);
	
	for(int i=0; i<64; i++){
		ImgOut[i] = ImgIn[i*64];
	}
	
	return ImgOut;

}

int chercheProche(int* tab, int tailleTab, int val){

	int index = 9999;
	int val = 9999;
	
	for(int i = 0; i< tailleTab; i++){
	
		if( abs(tab[i] - val) < 
	
	}

}

void mozaique(char* image){

	OCTET *ImgIn, *ImgOut;
	int nH, nW, nTaille;
		
	lire_nb_lignes_colonnes_image_pgm(image, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(nomImage, ImgIn, nH * nW);
		
	allocation_tableau(ImgOut, OCTET,  nTaille);
	
	int* tab = getTableauMoyenneImage(1000);
	
	for(int i=0; i<nH; i = i+8){
	
		for(int j=0; j<nW; j = j+8){
		
			int index = chercheProche(tab, 1000, ImgIn[i*nW+j]);
			
			for(int k=i; k< (i+8); k++){
				for(int l=j; l< (j+8); l++){
					ImgOut[k*nW+l] = moy;
				}
			}
		}	
	}
		
	ecrire_image_pgm("imgMozaique.pgm", ImgOut, 512, 512);
	

}


int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	int nbImage = 1000;
	int* tab = new int[nbImage];
   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	
	OCTET* divise = divisionImage(cNomImgLue, cNomImgEcrite);
	
	ecrire_image_pgm(cNomImgEcrite, divise, 512, 512);
	
	//tab = getTableauMoyenneImage(1000);

	return 1;
}
