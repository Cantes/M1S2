#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

void valeurs();

unsigned short* lireImage(char* nomImg){

	FILE* fichier;
	long tailleFichier;
  	size_t result;
	fichier = fopen(nomImg, "rb");
	unsigned short* buffer;
		
	if(fichier){
 		fseek (fichier, 0 , SEEK_END);
  		tailleFichier = ftell (fichier);
  		rewind (fichier);
  		
   		buffer = (unsigned short*) malloc (sizeof(unsigned short)*tailleFichier);		
 
  		if (buffer == NULL){
  			std::cerr << "Taille du buffer nulle" << std::endl;
  		}

  		result = fread (buffer,1,tailleFichier,fichier);
  		
  		if (result != tailleFichier){
  			std::cerr << "Erreur de lecture" << std::endl;
  		}
  		
	}else{
		std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
	}

	fclose(fichier);
	
	return buffer;
}

void valeurs(unsigned short* image, int dimX, int dimY, int dimZ){
	
	int min = 9999999;
	int max = 0;
	unsigned short save;
  		
	for(int i =0; i<dimX*dimY*dimZ; i++){
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


unsigned short getValue(unsigned short* image, int i, int j, int k){
	unsigned short save = (image[i*j+ (k*i*j)]>>8) | (image[i*j+(k*i*j)]<<8);
	return save;
}

void maillageSurfacique(unsigned short* image, int dimX, int dimY, int dimZ, float tailleVoxelX, float tailleVoxelY, float tailleVoxelZ, char* nomSortie, unsigned short seuil){

	FILE* fichierSortie;
	fichierSortie = fopen(nomSortie, "wab");
	
	fprintf(fichierSortie, "solid imagerie \n");
	fprintf(fichierSortie, "facet normal 0 0 0 \n");
	
	char* bufferSortie;

	for(int z=0; z < dimZ-1; z++){
		for(int x =0; x <dimX-1; x++){
			for(int y =0; y<dimY-1; y++){
			
				if(getValue(image,(x*tailleVoxelX),(y*tailleVoxelY),(z*tailleVoxelZ)) > seuil){
				
					for(int i = -1 ; i <2; i=i+2){
						if( getValue(image,(x+i)*tailleVoxelX,y*tailleVoxelY,z*tailleVoxelZ) < seuil){
							
							if(i < 0){
								fprintf(fichierSortie, "outer loop \n");
							
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+i+tailleVoxelX/2)*tailleVoxelX,(y-tailleVoxelY/2)*tailleVoxelY,(z-tailleVoxelZ/2)*tailleVoxelZ);
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+itailleVoxelX/2)*tailleVoxelX,(y+tailleVoxelY/2)*tailleVoxelY,(z-tailleVoxelZ/2)*tailleVoxelZ);
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+i+tailleVoxelX/2)*tailleVoxelX,(y+tailleVoxelY/2)*tailleVoxelY,(z+tailleVoxelZ/2)*tailleVoxelZ);
							
								fprintf(fichierSortie, "endloop \n \n");
							}else{
								fprintf(fichierSortie, "outer loop \n");
							
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+i-tailleVoxelX/2)*tailleVoxelX,(y-tailleVoxelY/2)*tailleVoxelY,(z-tailleVoxelZ/2)*tailleVoxelZ);
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+i-tailleVoxelX/2)*tailleVoxelX,(y+tailleVoxelY/2)*tailleVoxelY,(z-tailleVoxelZ/2)*tailleVoxelZ);
								fprintf(fichierSortie, "vertex %f %f %f \n",(x+i-tailleVoxelX/2)*tailleVoxelX,(y+tailleVoxelY/2)*tailleVoxelY,(z+tailleVoxelZ/2)*tailleVoxelZ);
							
								fprintf(fichierSortie, "endloop \n \n");							

							}

						}
						
						if( getValue(image,x*tailleVoxelX,(y+i)*tailleVoxelY,z*tailleVoxelZ) < seuil){
								
								
						}
						
						if( getValue(image,x*tailleVoxelX,y*tailleVoxelY,(z+i)*tailleVoxelZ) < seuil){
								
								
						}
					}
				
				}
			}	
		}
	}
	
	fprintf(fichierSortie, "endfacet \n");	
	fprintf(fichierSortie, "endsolid imagerie \n" );	
}

int main(int argc, char* argv[]){

	char fichier[] = "/auto_home/bcommandre/Bureau/M1_S2/TraitementImage/TP6/Image3D/engine/engine.img";
	char nomSortie[] = "sortie.stl";
	unsigned short* image;
	int dimX, dimY, dimZ;
	float tailleVoxelX,tailleVoxelY,tailleVoxelZ;
	
	sscanf (argv[1],"%d",&dimX);
	sscanf (argv[2],"%d",&dimY);
	sscanf (argv[3],"%d",&dimZ);
	sscanf (argv[4],"%f",&tailleVoxelX);
	sscanf (argv[5],"%f",&tailleVoxelY);
	sscanf (argv[6],"%f",&tailleVoxelZ);
	
	int seuil = 200;
	
	image = lireImage(fichier);

	maillageSurfacique(image, dimX, dimY, dimZ, tailleVoxelX, tailleVoxelY, tailleVoxelZ, nomSortie, seuil);
	//volumeRendering(fichier,sortie,1);
	
	return 0;
}









