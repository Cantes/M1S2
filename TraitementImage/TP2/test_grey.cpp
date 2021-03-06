#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

void dilate(char* entre,char* sortie){

	int nH, nW, nTaille,nB;
	
	OCTET *ImgIn, *ImgOut;
	
   	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);

	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			nB = 0;
			for(int k=-1; k<2; k++){
				for(int l=-1; l<2; l++){
					if(ImgIn[(i + k)*nW+(j+l)] == 0 ){
						nB++;
  					}
				}
			}
        	
			if(nB >= 5){
				ImgOut[i*nW+j] = 0;
			}else{
				ImgOut[i*nW+j] = ImgIn[i*nW+j];
			}
		}
	}	
		
	

	
	ecrire_image_pgm(sortie, ImgOut,  nH, nW); 
	
	free(ImgIn);
	free(ImgOut);
}

void erode(char* entre, char* sortie){


	int nH, nW, nTaille,nB;
	
	OCTET *ImgIn, *ImgOut;
	
   	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);

	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			nB = 0;
			for(int k=-1; k<2; k++){
				for(int l=-1; l<2; l++){
					if(ImgIn[(i + k)*nW+(j+l)] == 255 ){
						nB++;
  					}
				}
			}
        		
			if(nB >= 5){
				ImgOut[i*nW+j] = 255;
			}else{
				ImgOut[i*nW+j] = ImgIn[i*nW+j];
			}
		}
	}	
		
	ecrire_image_pgm(sortie, ImgOut,  nH, nW); 
	
	free(ImgIn);
	free(ImgOut);
}

void fermeture(char* entre, char* sortie){

	dilate(entre,sortie);
	erode(sortie,sortie);
}

void ouverture(char* entre, char* sortie){

	erode(entre,sortie);
	dilate(sortie,sortie);
}

void difference(char* entreSeuile, char* entreDilate, char* sortie){

	int nH, nW, nTaille;
	OCTET *ImgInSeuile, *ImgInDilate, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(entreSeuile, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgInSeuile, OCTET, nTaille);
	allocation_tableau(ImgInDilate, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	lire_image_pgm(entreSeuile, ImgInSeuile, nH * nW);
	lire_image_pgm(entreDilate, ImgInDilate, nH * nW);
	
	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if ( ImgInSeuile[i*nW+j] == 255 &&  ImgInDilate[i*nW+j] == 255){
				ImgOut[i*nW+j]=255;
			}else if ( ImgInSeuile[i*nW+j] == 0 &&  ImgInDilate[i*nW+j] == 0){
				ImgOut[i*nW+j]=255;
			}else{
				ImgOut[i*nW+j]=0;
			}
		}
	}
	
	ecrire_image_pgm(sortie, ImgOut,  nH, nW);
	
	free(ImgInSeuile);
	free(ImgInDilate);
	free(ImgOut);
}


void erodeSansSeuil(char* entre, char* sortie){


	int nH, nW, nTaille,nB;
	int* tab = new int[8];
	
	OCTET *ImgIn, *ImgOut;
	
   	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);

	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			nB = 0;
			for(int k=-1; k<2; k++){
				for(int l=-1; l<2; l++){
					if( (k != 0) && (l != 0)){
						tab[nB] =ImgIn[(i + k)*nW+(j+l)];
						nB++;	
					}
				}
			}
			
			int max = 0;
		
			for(int t =0; t<8; t++){
				if((tab[t] > max)){
					max = tab[t];
				}
			}
			
			ImgOut[i*nW+j] = max;		
		}
	}	
		
	ecrire_image_pgm(sortie, ImgOut,  nH, nW);
	
	free(ImgIn);
	free(ImgOut);
}

void dilateSansSeuil(char* entre, char* sortie){


	int nH, nW, nTaille,nB;
	int* tab = new int[8];
	
	OCTET *ImgIn, *ImgOut;
	
   	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);

	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			nB = 0;
			for(int k=-1; k<2; k++){
				for(int l=-1; l<2; l++){
					if( (k != 0) && (l != 0)){
						tab[nB] =ImgIn[(i + k)*nW+(j+l)];
						nB++;	
					}
				}
			}
			
			int min = 255;
			
			for(int t =0; t<8; t++){
				if((tab[t] < min) && (tab[t] != 0)){
					min = tab[t];
				}
			}
			
        		ImgOut[i*nW+j] = min;
        			
		}
	}	
		
	ecrire_image_pgm(sortie, ImgOut,  nH, nW);
	
	free(ImgIn);
	free(ImgOut);
}

int main(int argc, char* argv[])
{

  char* cNomImgLue = new char[256];
  char* cNomImgDilate = new char[256];
  char* cNomImgEcrite = new char[256];
  int nH, nW, nTaille, S;
   
   sscanf (argv[1],"%s",cNomImgLue) ;
  // sscanf (argv[2],"%s",cNomImgDilate);
   sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%s",cNomImgEcrite);
   
   //difference(cNomImgLue,cNomImgDilate,cNomImgEcrite);
   
   erodeSansSeuil(cNomImgLue, cNomImgEcrite);
   dilateSansSeuil(cNomImgEcrite, cNomImgEcrite);

  
   
   /*
   
   if(argc == 4){
 	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%d",&S);
	
	OCTET *ImgIn, *ImgOut;
   
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
  
 
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if ( ImgIn[i*nW+j] < S){
				ImgOut[i*nW+j]=255;
			}else{
				ImgOut[i*nW+j]=0;
			}
		}
	}

	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	
	free(ImgIn);
	free(ImgOut); 
	  
   }else{
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	
	//fermeture(cNomImgLue,cNomImgEcrite);

	//ouverture(cNomImgEcrite,cNomImgEcrite);
	
	//dilate(cNomImgLue, cNomImgEcrite);
	
	/*
	for(int i = 0; i<6; i++){
		if(i == 0){
			erode(cNomImgLue, cNomImgEcrite);
		}else{
			erode(cNomImgEcrite, cNomImgEcrite);
		}
	}
	
	for(int i=0; i<6; i++){
		dilate(cNomImgEcrite, cNomImgEcrite);
	}
	*/
	/*
	for(int i=0; i<3; i++){
		if(i == 0){
			dilate(cNomImgLue, cNomImgEcrite);
		}else{
			dilate(cNomImgEcrite, cNomImgEcrite);
		}
	}
	
	for(int i=0; i<6; i++){
		erode(cNomImgEcrite, cNomImgEcrite);
	}
	
	for(int i=0; i<3; i++){
		dilate(cNomImgEcrite, cNomImgEcrite);
	}
	*/
/*
   }

*/
   free(cNomImgLue);
   free(cNomImgDilate);
   free(cNomImgEcrite);
   

   return 1;
}
