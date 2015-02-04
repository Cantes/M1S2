#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

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






int main(int argc, char* argv[])
{
  char* cNomImgLue = new char[256];
  char* cNomImgEcrite = new char[256];
  int nH, nW, nTaille, S;
   
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
	
	
   }


   free(cNomImgLue);
   free(cNomImgEcrite);
   

   return 1;
}
