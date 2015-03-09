int CentreCercleCirconscrit(point A, point B, point C, point* O){

  //Stocke dans O les coordonnees du centre du cercle circonscrit a A, B et C
  //Renvoie 1 si ces 3 points sont alignes, 0 sinon et fait le calcul dans ce cas

    if(det(A,B,A,C)==0){return 1;}
   int xa=A.abscisse; int ya=A.ordonnee;
   int xb=B.abscisse; int yb=B.ordonnee;
   int xc=C.abscisse; int yc=C.ordonnee;
   (*O).abscisse=(int)((float)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(A,B,B,C)));
   (*O).ordonnee=(int)((float)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(B,C,A,B)));
   return 0;
}

---------------------------------------

void AffichageTestCercleCirconscrit(point sommet[4]){

  //Affiche les 4 points de sommet et le cercle circonscrit au trois premiers
  //Pour tester la fonction StrictementDansLeCercleCirconscrit

   ofstream output;
  output.open("Test.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<4;i++){
    output << sommet[i].abscisse << " " << sommet[i].ordonnee << " 2 0 360 arc"
           <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << sommet[i].abscisse+2 << " " << sommet[i].ordonnee << " moveto"
           <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i+1 << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;
  point O;  //Centre du cercle circonscrit
  if(CentreCercleCirconscrit(sommet[0],sommet[1],sommet[2],&O)==1){cout
    << "Points alignes" << endl; exit(1);}
  output << O.abscisse << " " << O.ordonnee << " 2 0 360 arc" <<endl;
  output << "0 setgray" <<endl;
  output << "fill" <<endl;
  output << O.abscisse+2 << " " << O.ordonnee << " moveto" <<endl;
  output << "/Courier findfont 15 scalefont setfont" << endl;
  output << "(O)" << " show" << endl;
  output << "stroke" << endl;
  output << endl;
  int r; //Rayon du cercle circonscrit
     r=(int)sqrt((double)NormeAuCarre(sommet[0],O));
     output << O.abscisse << " " << O.ordonnee << " " << r << " 0 360 arc" <<endl;
     output << "0 setgray" << endl;
     output << "stroke" << endl;
     output << "showpage"<< endl;
     output << endl;
}




