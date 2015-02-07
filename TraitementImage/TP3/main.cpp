#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "image_ppm.h"

using namespace std;


void histoGris(char* entre, char* cNomHisto){
	
	int niveau[256];
	int nW,nH,nTaille;
	
	for(int i = 0 ; i< 256; i++){
		niveau[i] = 0;
	}
	
	OCTET *ImgIn;
	
	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);
	
	fstream fichier(cNomHisto, ios::out | ios::trunc);
		
	for(int i =0; i < nH; i++){
		for(int j =0; j < nW; j++){
			niveau[ImgIn[i*nW+j]] = niveau[ImgIn[i*nW+j]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveau[i] <<  endl;
	}
	
	fichier.close();
}

void histoCouleur(char* entre, char* cNomHisto){

	int nH, nW, nTaille;
	int niveauR[256];
	int niveauV[256];
	int niveauB[256];

	OCTET *ImgIn;
   
   	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);	

	for(int i = 0 ; i< 256; i++){
		niveauR[i] = 0;
		niveauV[i] = 0;
		niveauB[i] = 0;
	}
	
	fstream fichier(cNomHisto, ios::out | ios::trunc);
	
	for (int i=0; i < nTaille3; i+=3){		
		niveauR[ImgIn[i]] = niveauR[ImgIn[i]] + 1;
		niveauV[ImgIn[i+1]] = niveauV[ImgIn[i+1]] + 1;
		niveauB[ImgIn[i+2]] = niveauB[ImgIn[i+2]] + 1;
	}

	free(ImgIn);

	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveauR[i] << " " << niveauV[i] << " " <<  niveauB[i] <<  endl;
	}

	fichier.close();	

}

void ddp(char* entre,char* file,char* histo){
	
	int niveau[256];
	float densite[256];
	int nW,nH,nTaille;
	
	for(int i = 0 ; i< 256; i++){
		niveau[i] = 0;
	}
	
	OCTET *ImgIn;
	
	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
	
	cout << nTaille << endl;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);
	
	fstream fichier(histo, ios::out | ios::trunc);
	fstream fichierDDP(file, ios::out | ios::trunc);
		
	for(int i =0; i < nH; i++){
		for(int j =0; j < nW; j++){
			niveau[ImgIn[i*nW+j]] = niveau[ImgIn[i*nW+j]] + 1;
		}	
	}
	
	for(int i =0; i < 256; i++){
		fichier << i << " " << niveau[i] <<  endl;
		if(i>0){
			densite[i] =( (float) niveau[i] / (float) nTaille ) + densite[i-1];
			fichierDDP << i << " " << densite[i] <<  endl;
		}else{
			densite[i] = (float) niveau[i] / (float) nTaille;
			fichierDDP << i << " " << densite[i] <<  endl;
		}
	}
	
	fichier.close();
	fichierDDP.close();
	
}

void expansionGris(char* entre, char* sortie){	
	
	int a0, a1, alpha, beta;
	int nH, nW, nTaille;

	OCTET *ImgIn, *ImgOut;
   
   	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_ppm(entre, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	
	a0 = 50;
	a1 = 200;
	
	alpha = (-255*a0)/(a1-a0);
	beta = 255/(a1-a0);
	
	
	for(int i =0; i < nH; i++){
		for(int j =0; j < nW; j++){
			ImgOut[i*nW+j] = alpha + beta*ImgIn[i*nW*j];
		}	
	}
	
	ecrire_image_ppm(sortie, ImgOut,  nH, nW);
	free(ImgIn);	
		
}

void expansionCouleur(char* entre, char* sortie){

	int a0, a1, alpha, beta;
	int nH, nW, nTaille;

	OCTET *ImgIn, *ImgOut;
   
   	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);
	
	
	a0 = 50;
	a1 = 200;
	
	alpha = (-255*a0)/(a1-a0);
	beta = 255/(a1-a0);
	
	for (int i=0; i < nTaille3; i+=3){
		ImgOut[i]= abs(alpha + beta*ImgIn[i]);
		ImgOut[i+1]= abs(alpha + beta*ImgIn[i+1]); 
		ImgOut[i+2]= abs(alpha + beta*ImgIn[i+2]);
	}

	ecrire_image_ppm(sortie, ImgOut,  nH, nW);
	free(ImgIn);	
}  




int retourneA0(char* nomFichier){
	//TODO   
}

int retourneA1(char* nomFichier){
	//TODO   
}

void seuilCouleur(char* entre, char* sortie){

	int nH, nW, nTaille;

	OCTET *ImgIn, *ImgOut;
   
   	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);
	
	for (int i=0; i < nTaille3; i+=3){
		for(int j=0; j<3; j++){
			if(ImgIn[i+j] < 50){
				ImgOut[i+j] = 50;
			}else if(ImgIn[i+j] > 200){
				ImgOut[i+j] = 200;
			}else{
				ImgOut[i+j] = ImgIn[i+j];
			}
		}
	}

	ecrire_image_ppm(sortie, ImgOut,  nH, nW);
	free(ImgIn);	
	
}

int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	char* cNomHisto = new char[256];
	int nH, nW, nTaille, S;
   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%s",cNomHisto);
     
     	//expansion(cNomImgLue,cNomImgEcrite);
     	//histoGris(cNomImgEcrite,cNomHisto);
     	//histoCouleur(cNomImgLue, cNomHisto);
     	
     	//expansionCouleur(cNomImgLue,cNomImgEcrite);
     	//histoCouleur(cNomImgEcrite, cNomHisto);
     	
     	//seuilCouleur(cNomImgLue,cNomImgEcrite);
     	//histoCouleur(cNomImgEcrite, cNomHisto);
     	
     	ddp(cNomImgLue,cNomImgEcrite,cNomHisto);

   return 1;
}
