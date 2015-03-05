#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

struct point {
	int x,y;
};


//fonction récupère les quatre voisins d'un point
void getVoisins(ImageBase& img, int x, int y, point v[]){

int xa = x - 1;
int xb = x + 1;
int ya = y - 1;
int yb = y + 1;

//verification des bords
if (xa < 0) xa = 0;
if (xb > img.getWidth()- 1) xb = img.getWidth() - 1;
if (ya < 0) ya = 0;
if (yb > img.getHeight() - 1) yb = img.getHeight() - 1;

//remplissage du tableau
 v[0].x = xa;
 v[0].y = y;

 v[1].x = xb;
 v[1].y = y;

 v[2].x = x;
 v[2].y = ya;

 v[3].x = x;
 v[3].y = yb;

}

//======fonction qui va colorer les voisins d'un pixel
void colorVoisinsIn(ImageBase& img, int x, int y, int color, int canal)
{
    //image en ndg ou en couleur
    int decal = img.getColor()?3:1;

    //tableau contenant les points voisins
    point voisins[4];
    getVoisins(img,x,y,voisins);//le tableau est rempli avec les 4 voisins du point

    for(int i =0; i< 4; i++)
    {
        int a = voisins[i].x;
        int b = voisins [i].y;
        img[a*decal][b*decal+canal] = color;
    }
}


//===============fonction qui colore toute l'image===============
void colorAllIn(ImageBase& im, int val)
{
	for (int x = 0; x < im.getWidth(); ++x) {
		for (int y = 0; y < im.getHeight(); ++y) {
                im[x][y] = val;
		}
	}
}

//================fonction qui modifie la valeur des pixels sur tout une image================
ImageBase setToVal(ImageBase& in, int val)//val2 correspond à ce qui va être dilater
{
    //création de l'image de sortie
    ImageBase out(in.getWidth(),in.getHeight(), in.getColor());

    //on commence par prendre la couleur qui ne sera pas dilatée et on l'étend sur toute l'image
    //pour l'érosion c'est le blanc qui dilaté et pour la dilatation c'est le noir
    colorAllIn(out, (val==255)?0:255);

    //on prend chaque pixel et selon sa couleur on colore ses voisins et lui même
    for (int i =0; i< in.getWidth();i++)
    {
        for(int j =0; j< in.getHeight();j++)
        {
            if(in[i][j]==val)
            {
                colorVoisinsIn(out,i,j,val,0);
                out[i][j] = val;
            }
        }
    }
    return out;
}

bool getSame(int x , int y, ImageBase& in, ImageBase& dil)
{
    return in[x][y]==dil[x][y];
}

ImageBase difference (ImageBase& in,ImageBase dil)
{

    ImageBase out = ImageBase(in.getWidth(),in.getHeight(),in.getColor());
    for (int x = 0; x < in.getWidth();x++)
    {
        for(int y = 0; y< in.getHeight();y++)
        {
            if(getSame(x,y,in,dil)) out[x][y] = 255;
            else out[x][y] = 0;
        }
    }
return out;
}


//=================fonctions de traitement====================
ImageBase erosion (ImageBase& in)
{
    //ici c'est le blanc qui sera dilaté
  ImageBase out =  setToVal(in,255);
  return out;
}

ImageBase dilatation (ImageBase& in)
{
    //ici c'est l'objet (le noir) qui sera dilaté
    ImageBase out = setToVal(in, 0);
    return out;
}

ImageBase fermeture (ImageBase& in)
{
     ImageBase out = setToVal(in, 0);
     return erosion(out);
}

ImageBase ouverture (ImageBase& in)
{
    ImageBase out = setToVal(in, 255);
    return dilatation(out);
}


int main(int argc, char **argv) {



	ImageBase imIn;
	imIn.load("09.pgm");


	ImageBase out = ouverture(imIn);

	out.save("ouvrendg.pgm");
}
