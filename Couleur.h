#include<iostream>
using namespace std;

#ifndef COULEUR_H
#define COULEUR_H

class Couleur
{
    private:
        float r;
        float g;
        float b;

    public:
        Couleur(float r_, float g_, float b_);
        Couleur();

        float getR();
        float getG();
        float getB();

        void setR(float r_);
        void setG(float g_);
        void setB(float b_);

        Couleur operator+(const Couleur &c) const;
        Couleur operator-(const Couleur &c) const;
        Couleur operator*(const float &l) const;
        Couleur operator*(const Couleur &c) const;
        Couleur operator/(const float &l) const;


    friend ostream &operator<<(std::ostream &out, Couleur &couleur);
};


#endif // COULEUR_H
