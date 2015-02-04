
#include "../TP1/Point.h"

void HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU){
	
	Point* tab = new Point[nbU];
	double f1 = 0;
	double f2 = 0;
	double f3 = 0;
	double f4 = 0;
	
	
	
	for(int i=0; i<nbU; i++){
		f1 = 2*pow((double) i/nbU,3) - 3*pow((double)i/nbU,2) + 1;	
		f2 = -2*pow((double)i/nbU,3) + 3*pow((double)i/nbU,2);
		f3 = pow((double)i/nbU,3) - 2*pow((double)i/nbU,2) + (double)i/nbU;
		f4 = pow((double)i/nbU,3) - pow((double)i/nbU,2);
		
		cout << f1 << "," << f2 << "," << f3 << "," << f4 << endl;
		
		Point a = Point(f1*P0.getX() + f2*P1.getX() + f3*V0.getX() + f4*V1.getX(),
				f1*P0.getY() + f2*P1.getY() + f3*V0.getY() + f4*V1.getY(),
				f1*P0.getZ() + f2*P1.getZ() + f3*V0.getZ() + f4*V1.getZ()
			);	
		
		tab[i] = a;
	}
	/*
	for(int i=0; i<nbU; i++){
		tab[i].affiche();
	}*/	

}

int main(int argc, char **argv){  

	Point P0 = Point(0,0,0);
	Point P1 = Point(2,0,0);
	Vector V0 = Vector(1,1,0);
	Vector V1 = Vector(1,-1,0);
	
	HermiteCubicCurve(P0,P1,V0,V1, 10);
}
