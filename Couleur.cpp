#include "Couleur.h"

Couleur::Couleur()
{
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Couleur::Couleur(float r_, float g_, float b_)
{
    r = r_;
    g = g_;
    b = b_;
}

float Couleur::getR(){
    return r;
}

float Couleur::getG(){
    return g;
}

float Couleur::getB(){
    return b;
}


void Couleur::setR(float r_){
    r = r_;
}

void Couleur::setG(float g_){
    g = g_;
}

void Couleur::setB(float b_){
    b = b_;
}

Couleur Couleur::operator+(const Couleur &c) const{
    return Couleur(r+c.r, g+c.g, b+c.b);
}

Couleur Couleur::operator-(const Couleur &c) const{
    return Couleur(r-c.r, g-c.g, b-c.b);
}

Couleur Couleur::operator*(const float &l) const{
    return Couleur(l*r, l*g, l*b);
}

Couleur Couleur::operator*(const Couleur &c) const{
    return Couleur(r*c.r, g*c.g, b*c.b);
}

Couleur Couleur::operator/(const float &l) const{
    float inv = 1/l;
    return Couleur(inv*r, inv*g, inv*b);
}

std::ostream &operator<<(std::ostream &out, Couleur &couleur){
    out << "(" << couleur.r << ", " << couleur.g << ", " << couleur.b << ")";
    return out;
}
