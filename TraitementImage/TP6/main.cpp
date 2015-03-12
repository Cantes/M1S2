#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

int dimX = 0;
int dimY = 0;
int dimZ = 0;
int tailleImage;
unsigned short* image;

void valeurs();

void lireImage(char* nomImg){

	FILE* fichier;
	long tailleFichier;
  	size_t result;
	fichier = fopen(nomImg, "rb");
		
	if(fichier){
 		fseek (fichier, 0 , SEEK_END);
  		tailleFichier = ftell (fichier);
  		rewind (fichier);
  		
  		tailleImage = sizeof(unsigned short)*tailleFichier;
   		image = (unsigned short*) malloc (sizeof(unsigned short)*tailleFichier);		
 
  		if (image == NULL){
  			std::cerr << "Taille du buffer nulle" << std::endl;
  		}

  		result = fread (image,1,tailleFichier,fichier);
  		
  		if (result != tailleFichier){
  			std::cerr << "Erreur de lecture" << std::endl;
  		}
  		

	}else{
		std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
	}
	
	fclose(fichier);
}

void valeurs(){
	
	int min = 9999999;
	int max = 0;
	unsigned short save;
  		
	for(int i =0; i<tailleImage/2; i++){
		save = (image[i]>>8) | (image[i]<<8);
		if(save< min){
			min = save ;
		}
  			
		if(save > max){
			max = save;
		}
	}
		
	std::cout << "Valeur minimale : " << min << std::endl;
	std::cout << "Valeur maximale : " << max << std::endl;
}

int getValue(int i, int j, int k){
	unsigned short save = (image[(i*j*k)/2]>>8) | (image[(i*j*k)/2]<<8);
	return save;
}

int main(int argc, char* argv[]){

	char fichier[] = "/home/cantes/Bureau/M1S2/TraitementImage/TP6/Image3D/BEAUFIX/beaufix.img";
	//char fichier[] = "/auto_home/bcommandre/Bureau/M1_S2/TraitementImage/TP6/Image3D/BEAUFIX/beaufix.img";
	//char fichier[] = "/home/cantes/Bureau/M1S2/TraitementImage/TP6/Image3D/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img";
	
	sscanf (argv[1],"%d",&dimX);
	sscanf (argv[2],"%d",&dimY);
	sscanf (argv[2],"%d",&dimZ);
	
	lireImage(fichier);	
	std::cout << getValue(200,200,200) << std::endl;
	valeurs();
	
	return 0;
}









