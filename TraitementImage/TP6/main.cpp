#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

int dimX = 0;
int dimY = 0;
int dimZ = 0;
unsigned short* image;

void valeurs();

void lireImage(char* nomImg){

	FILE* fichier;
	FILE* sortie;
	long tailleFichier;
  	size_t result;
	fichier = fopen(nomImg, "rb");
	sortie  = fopen("sortie.img", "wb");
		
	if(fichier){
 		fseek (fichier, 0 , SEEK_END);
  		tailleFichier = ftell (fichier);
  		rewind (fichier);
 
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
	
	result = fwrite (image,1,tailleFichier,sortie);
  		
  	if (result != tailleFichier){
  		std::cerr << "Erreur de lecture" << std::endl;
  	}
	
	fclose(fichier);
	fclose(sortie);
}

void valeurs(){

	int min = 9999;
	int max = 0;
	
	int taille = (dimX*dimY)/2;
		
	for(int z = 0; z<dimZ; z++){
		for(int i =0; i<taille; i++){
			if(image[i + (taille*z)] > max){
				max = image[i + (taille*z)];
			}
			
			if(image[i + (taille*z)] < min){
				min = image[i + (taille*z)];
			}
		}
	}
		
	std::cout << "Valeur minimale : " << min << std::endl;
	std::cout << "Valeur maximale : " << max << std::endl;
}

int getValue(int i, int j, int k){
	
	return image[(i*j)/2 * k/2];
}

int main(int argc, char* argv[]){

	char fichier[] = "/auto_home/bcommandre/Bureau/M1_S2/TraitementImage/TP6/Image3D/BEAUFIX/beaufix.img";
	
	sscanf (argv[1],"%d",&dimX);
	sscanf (argv[2],"%d",&dimY);
	sscanf (argv[2],"%d",&dimZ);
	
	lireImage(fichier); 
	
	//std::cout << getValue(32,51,0) << std::endl;
	valeurs();
	
	return 0;
}









