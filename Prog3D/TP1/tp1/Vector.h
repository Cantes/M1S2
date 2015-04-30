#ifndef VECTOR_H
#define VECTOR_H


class Vector
{

    public:
    //constructeurs
        Vector();
        Vector(double x, double y, double z);
        Vector (const Vector& v);
        virtual ~Vector();

     //getteurs
     double getX ();
     double getY ();
     double getZ ();

     //setteurs
     void setX (double newX);
     void setY (double newY);
     void setZ (double newZ);


     double Norme ();
     void Normalized ();
     double Scalar (Vector vector2);
     Vector vectoriel (Vector v2);
     double angle (Vector v);
     void afficher();

    protected:
    private: double x,y,z;
};

#endif // VECTOR_H
