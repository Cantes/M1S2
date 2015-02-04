#include "ImageBase.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void profil(char* fileName, bool ligne, int num){
	
	ImageBase imIn;
	imIn.load(fileName);
	
	fstream fichier("profil.dat", ios::out | ios::trunc);
	
	if(ligne){
		for(int j =0; j < imIn.getWidth(); j++){
			fichier << (int) imIn[num][j] << endl;
		}
	}else{
		for(int i =0; i < imIn.getHeight(); i++){
			fichier << (int) imIn[i][num] << endl;
		}
	}
	
	fichier.close();
}

void histoGris(char* fileName){
	
	int niveau[256];
	
	for(int i = 0 ; i< 256; i++){
		niveau[i] = 0;
	}
	
	ImageBase imIn;
	imIn.load(fileName);
	
	fstream fichier("histoGris.dat", ios::out | ios::trunc);
	
	for(int i =0; i < imIn.getHeight(); i++){
		for(int j =0; j < imIn.getWidth(); j++){
			niveau[imIn[i][j]] = niveau[imIn[i][j]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveau[i] <<  endl;
	}
	
	fichier.close();
}

void histoCouleur(char* fileName){

	int niveauR[256];
	int niveauV[256];
	int niveauB[256];
	
	ImageBase imIn;
	imIn.load(fileName);
	
	fstream fichier("histoCouleur.dat", ios::out | ios::trunc);
	
	for(int i = 0 ; i< 256; i++){
		niveauR[i] = 0;
		niveauV[i] = 0;
		niveauB[i] = 0;
	}
	
	for(int i =0; i < imIn.getHeight(); i++){
		for(int j =0; j < imIn.getWidth(); j++){
			niveauR[imIn[i][j*3]] = niveauR[imIn[i][j*3]] + 1;
			niveauV[imIn[i][(j*3) + 1]] = niveauV[imIn[i][(j*3) + 1]] + 1;
			niveauB[imIn[i][(j*3) + 2]] = niveauB[imIn[i][(j*3) + 2]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveauR[i] << " " << niveauV[i] << " " <<  niveauB[i] <<  endl;
	}

	fichier.close();
}

void seuilCouleur(char* fileName){

	ImageBase imIn;
	imIn.load(fileName);
	
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight() * 3; ++x)
	{
		for(int y = 0; y < imIn.getWidth(); y = y+3)
		{
			for(int k = 0; k < 3; k++){
				if (imIn[x][y + k] < 30){
					imOut[x][y + k] = 0;
				}else if (imIn[x][y + k] < 100){
					imOut[x][y + k] = 85;
				}else if (imIn[x][y + k] < 180){
					imOut[x][y + k] = 170;
				}else{
					imOut[x][y+ k] = 255;
				}
			} 
		}
	}
	
	char lenaModif[] = "lenaModif.ppm";
	imOut.save(lenaModif);	
}


int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	int S,S1,S2,S3;
  
/*	if (argc != 4) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
		return 1;
	}*/
	
	if (argc == 4){
		sscanf (argv[1],"%s",cNomImgLue) ;
		sscanf (argv[2],"%s",cNomImgEcrite);
		sscanf (argv[3],"%d",&S);
	}else if (argc == 5){
		sscanf (argv[1],"%s",cNomImgLue) ;
		sscanf (argv[2],"%s",cNomImgEcrite);
		sscanf (argv[3],"%d",&S1);
		sscanf (argv[4],"%d",&S2);
	}else if (argc == 6){
		sscanf (argv[1],"%s",cNomImgLue) ;
		sscanf (argv[2],"%s",cNomImgEcrite);
		sscanf (argv[3],"%d",&S1);
		sscanf (argv[4],"%d",&S2);
		sscanf (argv[5],"%d",&S3);	
	}

	
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

//Pour un seuil en 2 parties
/*	for(int x = 0; x < imIn.getHeight(); ++x)
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] < S) 
				imOut[x][y] = 0;
			else imOut[x][y] = 255;
		}
	}	*/
		
	//Pour un seuil en 3 parties
/*	for(int x = 0; x < imIn.getHeight(); ++x)
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] < S1){
				imOut[x][y] = 0;
			}else if (imIn[x][y] < S2){
				imOut[x][y] = 128;
			}else{
				imOut[x][y] = 255;
			}
		}
	}*/
	
	//Pour un seuil en 4 parties
	for(int x = 0; x < imIn.getHeight(); ++x)
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] < S1){
				imOut[x][y] = 0;
			}else if (imIn[x][y] < S2){
				imOut[x][y] = 85;
			}else if (imIn[x][y] < S3){
				imOut[x][y] = 170;
			}else{
				imOut[x][y] = 255;
			}
		}
	}
		
	imOut.save(cNomImgEcrite);
		

	profil(cNomImgLue,true,10);
	histoGris(cNomImgLue);
	
	char lena[] = "lena.ppm";
	histoCouleur(lena);
	seuilCouleur(lena);
	
	///////////////////////////////////////// Exemple de création d'une image couleur
	ImageBase imC(50, 100, true);

	for(int y = 0; y < imC.getHeight(); ++y)
		for(int x = 0; x < imC.getWidth(); ++x)
		{
			imC[y*3][x*3+0] = 200; // R
			imC[y*3][x*3+1] = 0; // G
			imC[y*3][x*3+2] = 0; // B
		}
	
	
	char nomCouleur[] = "imC.ppm";
	imC.save(nomCouleur);	
		


	///////////////////////////////////////// Exemple de création d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for(int y = 0; y < imG.getHeight(); ++y)
		for(int x = 0; x < imG.getWidth(); ++x)
			imG[y][x] = 50;

	char nomGris[] = "imG.pgm";
	imG.save(nomGris);




	ImageBase imC2, imG2;
	
	///////////////////////////////////////// Exemple lecture image couleur
	char lectureCouleur[] = "imC.ppm";
	imC2.load(lectureCouleur);
	///////////////////////////////////////// Exemple lecture image en niveau de gris
	char lectureGris[] = "imG.pgm";
	imG2.load(lectureGris);
	
	

	///////////////////////////////////////// Exemple de récupération d'un plan de l'image
	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	char lectureR[] = "R.pgm";
	R->save(lectureR);
	delete R;
	


	return 0;
}
