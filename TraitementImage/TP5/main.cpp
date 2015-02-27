#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "image_ppm.h"

using namespace std;

int* calculsImage(OCTET* img, int nH, int nW);

void couleurToGris(char* entre, char* sortie){
	
	int nH, nW, nTaille;
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
   	
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);	
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	for(int i=0; i<nTaille3; i++){
		ImgOut[i / 3] = 0.2125*ImgIn[i] + 0.7154*ImgIn[i + 1] + 0.0721*ImgIn[i + 2]; 
	}
	
	ecrire_image_pgm(sortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);
}

void division(char* entre){
	
	int nH, nW, nTaille;
	char* sortie ;
	
	sortie = "sortie.pgm";
	
	OCTET *ImgIn, *ImgOut;
		
	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);
		
	allocation_tableau(ImgOut, OCTET,  nTaille);

	int* tab = calculsImage(ImgIn, nH, nW);

	for (int i=0; i <= nH; i++){
		for (int j=0; j <= nW; j++){
			if(i < 0.5*nH && j< 0.5*nW){
				ImgOut[i*nW+j] = tab[0];
			}else if(i < 0.5*nH && j> 0.5*nW){
				ImgOut[i*nW+j] = tab[1];
			}else if(i > 0.5*nH && j< 0.5*nW){
				ImgOut[i*nW+j] = tab[2];
			}else{
				ImgOut[i*nW+j] = tab[3];
			}
		}
	}
	
	ecrire_image_pgm(sortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);

	
}

int* calculsImage(OCTET* img, int nH, int nW){

	int* tabMoy = new int[4];
	int* tabVariance = new int[4];
	
	int nTaille = nH * nW;

	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if(i < 0.5*nH && j< 0.5*nW){
				tabMoy[0] = tabMoy[0] + img[i*nW+j];
				tabVariance[0] = tabVariance[0] + pow(img[i*nW+j],2);
			}else if(i < 0.5*nH && j> 0.5*nW){
				tabMoy[1] = tabMoy[1] + img[i*nW+j];
				tabVariance[1] = tabVariance[1] + pow(img[i*nW+j],2);
			}else if(i > 0.5*nH && j< 0.5*nW){
				tabMoy[2] = tabMoy[2] + img[i*nW+j];
				tabVariance[2] = tabVariance[2] + pow(img[i*nW+j],2);
			}else{
				tabMoy[3] = tabMoy[3] + img[i*nW+j];
				tabVariance[3] = tabVariance[3] + pow(img[i*nW+j],2);
			}
		}
	}
	

	
	for(int i=0; i<4; i++){
		tabMoy[i] = tabMoy[i] / (nTaille/4);
		cout << "Moyenne R" << (i+1) << " : " << tabMoy[i] << endl;
		cout << "Variance R" << (i+1) << " : " << (tabVariance[i]/ (nTaille/4)) - pow(tabMoy[i],2) << endl;
		cout << endl;
	}
	
	return tabMoy;

}

int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	char* cNomHisto = new char[256];
	int nH, nW, nTaille;
   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	//sscanf (argv[3],"%s",cNomHisto);
     
	//couleurToGris(cNomImgLue, cNomImgEcrite);
	
	division(cNomImgLue);

	return 1;
}
