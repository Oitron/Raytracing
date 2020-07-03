#include<iostream>
#include "tools.h"
using namespace std;

#ifndef VECTEUR3_H
#define VECTEUR3_H

class Vecteur3
{
    private:
        float x;
        float y;
        float z;

    public:
        Vecteur3(float x_, float y_, float z_);
        Vecteur3();


        float getX();
        float getY();
        float getZ();

        void setX(float x_);
        void setY(float y_);
        void setZ(float z_);


        float length_square() const;
        float length() const;
        Vecteur3 operator+(const Vecteur3 &v) const;
        Vecteur3 operator-(const Vecteur3 &v) const;
        Vecteur3 operator*(const Vecteur3 &v) const;
        Vecteur3 operator*(const float &l) const;
        Vecteur3 operator/(const float &l) const;

        Vecteur3 normalize() const;

        float scalar(const Vecteur3 &v) const;
        Vecteur3 cross(const Vecteur3 &v) const;



    friend ostream &operator<<(std::ostream &out, Vecteur3 &vect);
};





#endif // VECTEUR3_H
