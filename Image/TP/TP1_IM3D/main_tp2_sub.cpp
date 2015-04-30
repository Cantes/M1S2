#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *token;
unsigned short ***data = NULL;
int dimX,dimY,dimZ;
unsigned short Pmin = 64000;
unsigned short Pmax = 0;


void readingImg(char* filename, const char* filenameConst){

//récupération des dimensions
     token = strtok(filename,".x");//donc il ne faut pas qu'il y ait de x en dehors des séparateurs
     if (token != NULL){

           // printf("nom du fichier : %s\n",token);

                token = strtok(NULL,"x");
                 dimX = atoi(token);
              //  printf("dimX is:  %i\n", dimX);

                token = strtok(NULL,"x");
                 dimY = atoi(token);
               //  printf("dimY is:  %i\n", dimY);

                token = strtok(NULL,"x");
                 dimZ = atoi(token);
               // printf("dimZ is:  %i\n", dimZ);
                }

 //fonction d'ouverture du fichier
   // printf("filename : %s\n", filenameConst);
    FILE* IMG = fopen(filenameConst,"rb");

//on vérifie que le fichier n'est pas vide
    if(IMG == NULL){
        printf("error\n");
        exit(-1);
    }

//data[width*height*depth]
//y*width+x + z*width*height
//création d'une matrice 3D contenant les voxels de chaque lignes et le tout pour chaque tranche
    data = (unsigned short***)malloc(dimZ*sizeof(unsigned short**));
    for (int z = 0; z< dimZ;z++){//parcours des coupes
        data[z] =(unsigned short**) malloc (dimX*sizeof(unsigned short*));
        for(int x=0;x<dimX;x++){//parcours des lignes
            data[z][x]=(unsigned short*)malloc(dimY*sizeof(unsigned short));
            for(int y =0;y<dimY;y++){

                unsigned char oct1;
                unsigned char oct2;

                fread(&oct1,1,1, IMG);
                fread(&oct2,1,1, IMG);

                data[z][x][y]=((unsigned short)oct1 * 256)  + (unsigned short)oct2;
                if(data[z][x][y]<Pmin) {Pmin = data[z][x][y];}
                //printf("pmin : %i\n",Pmin);}
                if(data[z][x][y]>Pmax) {Pmax = data[z][x][y];}
                //printf("pmax : %i\n",Pmax);}
            }
        }
    }

}

unsigned short getValue(int i,int j,int k){
return data[i][j][k];}

void writingMAX(char* filename){

     int Pmax2;
//on créer un tableau dans lequel on rangera les valeurs de i'image 2D finale
    unsigned short int** dataNew = (unsigned short int**)malloc(dimX*sizeof(unsigned short int*));//tableau 2D pour une image 2D
    for(int x = 0; x < dimX; x++){
        dataNew[x] = (unsigned short int*)malloc(dimY*sizeof(unsigned short int));
    }
//on crée le fichier qui sera l'image de sortie
    FILE* OUT = fopen(filename, "wb");

	for(int i = 0;i<dimX;i++){//parcours des lignes
		for(int j = 0;j < dimY;j++){

		    Pmax2 = 0;
            for (int n = 0; n< dimZ;n++){//parcours des coupes
                //on recherche le point max à travers toutes les coupes
                if(data[n][i][j]>Pmax2) Pmax2 = data[n][i][j];
            }
             dataNew[i][j] = Pmax2;

            unsigned char c1;
            unsigned char c2;
            c1 = (unsigned char)(Pmax2 / 256);
            c2 = (unsigned char)(Pmax2 % 256);
            fwrite(&c1, 1, 1, OUT);
            fwrite(&c2, 1, 1, OUT);
        }
    }
    fclose(OUT);
}

void writingMin(char* filename){

    int Pmin2;
  /*  unsigned short** dataNew = (unsigned short**)malloc(dimX*sizeof(unsigned short*));//tableau 2D pour une image 2D
    for(int x = 0; x < dimX; x++){
        dataNew[x] = (unsigned short*)malloc(dimY*sizeof(unsigned short));
    }

	for(int i = 0;i<dimX;i++){//parcours des lignes
		for(int j = 0;j < dimY;j++){
		    Pmin2 = 0;
            for (int n = 0; n< dimZ;n++){//parcours des coupes
                if(data[n][i][j]>Pmin2) Pmin2 = data[n][i][j];
            }
             dataNew[i][j]= Pmin2;
        }
    }

    FILE* OUT = fopen(filename, "wb");
    for(int i=0;i<dimY;i++){//parcours des lignes
		for(int j =0;j < dimX;j++){
         unsigned char c1;
         unsigned char c2;

         c1 = (unsigned char)(dataNew[i][j]/256);
         c2 = (unsigned char)(dataNew[i][j]%256);

         fwrite(&c1, 1, 1, OUT);
         fwrite(&c2, 1, 1, OUT);
		}
    }
    fclose(OUT);*/
 FILE* OUT = fopen(filename, "wb");
	for(int i = 0;i<dimX;i++){//parcours des lignes
		for(int j = 0;j < dimY;j++){
		    int Pmin2 = 64000;
            for (int n = 0; n< dimZ;n++){//parcours des coupes
                if(data[n][i][j]<Pmin2) Pmin2 = data[n][i][j];
            }
             unsigned char c1;
             unsigned char c2;

             c1 = (unsigned char)(Pmin2/256);
             c2 = (unsigned char)(Pmin2%256);

             fwrite(&c1, 1, 1, OUT);
             fwrite(&c2, 1, 1, OUT);
        }
    }
  fclose(OUT);
}

void writingAIP(char* filename){
    unsigned short** dataNew = (unsigned short**)malloc(dimX*sizeof(unsigned short*));//tableau 2D pour une image 2D
        for(int x = 0; x < dimX; x++){
            dataNew[x] = (unsigned short*)malloc(dimY*sizeof(unsigned short));
        }

   // int moy = 0;
        for(int i = 0;i<dimX;i++){//parcours des lignes
            for(int j = 0;j < dimY;j++){
          //      int som = 0;
                for (int n = 0; n< dimZ;n++){//parcours des coupes
                    dataNew[i][j] = data[n][i][j]/dimZ;
                    //printf("som pour l'image :%i = %i\n",n,som);
                }
                 //moy = som/dimZ;
                 //printf("moy pour l'image : %i\n",moy);
            }
        }
     FILE* OUT = fopen(filename, "wb");
    for(int i=0;i<dimY;i++){//parcours des lignes
		for(int j =0;j < dimX;j++){
         unsigned char c1;
         unsigned char c2;

         c1 = (unsigned char)(dataNew[i][j] / 256);
         c2 = (unsigned char)(dataNew[i][j] % 256);

         fwrite(&c1, 1, 1, OUT);
         fwrite(&c2, 1, 1, OUT);
		}
    }
    fclose(OUT);


}
void seuillage(int seuil){

    unsigned short** dataNew = (unsigned short**)malloc(dimX*sizeof(unsigned short*));//tableau 2D pour une image 2D
        for(int x = 0; x < dimX; x++){
            dataNew[x] = (unsigned short*)malloc(dimY*sizeof(unsigned short));
        }
        for(int i = 0;i<dimX;i++){//parcours des lignes
            for(int j = 0;j < dimY;j++){
                for (int n = 0; n< dimZ;n++){
                    if(data[i][j][j] < seuil) dataNew[i][j] = seuil;
                }
            }
        }
}


int main(int argc, char **argv) {

    char Tstring[] = "whatisit.301x324x56.1.1.1.4.img";

    readingImg(Tstring,"whatisit.301x324x56.1.1.1.4.img");
   // writingMAX((char*)"orange_max.0.raw");
    //writingMin((char*)"FOOT_min.0.raw");
    writingAIP((char*)"WHAT_moy.0.raw");
//visuflag = 1 pour le max
//visuflag = 2 pour la moyenne
//visuflag = 3 pour le min

//===========================seuillage================
//seuillage(37);



return 0;
}

