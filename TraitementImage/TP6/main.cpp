#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "image_ppm.h"


int calculMoyenne(OCTET* image, int position, int nW){

	int result = 0;
	int nb = 0;
	
	for(int i = -1; i<2; i++){
		for(int j =-1; j<2; j++){
			if(image[(i + position)*nW+j] != 0){
				result += image[(i + position)*nW+j];
				nb++;
			}
		}
	}	
	
	return result / nb;
	
}

void reconstructionParMoyenne(char* nomImageLue, char* nomImageSortie){

	int nH, nW, nTaille;
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(nomImageLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(nomImageLue, ImgIn, nH * nW);
		
	allocation_tableau(ImgOut, OCTET,  nTaille);
	
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
		
			if(ImgIn[i*nW+j] < 30){
				ImgIn[i*nW+j] = 0;	
			}
			
			if( ImgIn[i*nW+j] == 0){
				ImgOut[i*nW+j] = calculMoyenne(ImgIn,i,nW);
			}else{
				ImgOut[i*nW+j] = ImgIn[i*nW+j];
			}
		}
	}
	
	ecrire_image_pgm(nomImageSortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);
	
}

void reconstructionParDilatation(char* entre,char* sortie){

	int nH, nW, nTaille;
    	std::vector<int> listeValeur;
	OCTET *ImgIn, *ImgOut;
	
   	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
  	//allocation_tableau(ImgIn, OCTET, nTaille);
  	//lire_image_pgm(entre, ImgIn, nH * nW);
  	
	allocation_tableau(ImgOut, OCTET, nTaille);
	lire_image_pgm(entre, ImgOut, nH * nW);

	bool fin = false;
	
	while(!fin){
		fin = true;
		for (int i=1; i < nH-1; i++){
			for (int j=1; j < nW-1; j++){

				if(ImgOut[i*nW+j] < 15){
		      			fin = false;
					for(int k=-1; k<2; k++){
						for(int l=-1; l<2; l++){
							if(ImgOut[(i + k)*nW+(j+l)] > 15 ){
								listeValeur.push_back(ImgOut[(i + k)*nW+(j+l)]);
	  						}
						}
					}
				
					if(!listeValeur.empty()){
						int max = 0;
						for(int i=0; i<listeValeur.size(); i++){
							if(listeValeur.at(i) > max){
								max = listeValeur.at(i);
							}
						}
						
						ImgOut[i*nW+j] = max;
						
						listeValeur.clear();

					}/*else{
						ImgOut[i*nW+j] = ImgOut[i*nW+j];
					}*/						
				}/*else{
					ImgOut[i*nW+j] = ImgOut[i*nW+j];
				}*/
				
			}
		}
		/*
		for (int i=0; i < nH; i++){
			for (int j=0; j < nW; j++){
				ImgIn[i*nW+j] = ImgOut[i*nW+j];
			}
		}*/
			
	}
	
		
	ecrire_image_pgm(sortie, ImgOut,  nH, nW); 
	
	//free(ImgIn);
	free(ImgOut);

}

int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	//reconstructionParMoyenne(cNomImgLue,cNomImgEcrite);
	
	reconstructionParDilatation(cNomImgLue,cNomImgEcrite);

	return 1;
}
