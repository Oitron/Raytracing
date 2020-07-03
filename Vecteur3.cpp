#include<iostream>
using namespace std;
#include "Vecteur3.h"
#include <math.h>

Vecteur3::Vecteur3(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vecteur3::Vecteur3(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

float Vecteur3::getX(){
    return x;
}
float Vecteur3::getY(){
    return y;
}
float Vecteur3::getZ(){
    return z;
}

void Vecteur3::setX(float x_){
    x = x_;
}
void Vecteur3::setY(float y_){
    y = y_;
}
void Vecteur3::setZ(float z_){
    z = z_;
}

float Vecteur3::length_square() const{
    return x*x+y*y+z*z;
}

float Vecteur3::length() const{
    return sqrt(x*x+y*y+z*z);
}

Vecteur3 Vecteur3::operator+(const Vecteur3 &v) const{
    return Vecteur3(x+v.x, y+v.y, z+v.z);
}

Vecteur3 Vecteur3::operator-(const Vecteur3 &v) const{
    return Vecteur3(x-v.x, y-v.y, z-v.z);
}

Vecteur3 Vecteur3::operator*(const Vecteur3 &v) const{
    return Vecteur3(x*v.x, y*v.y, z*v.z);
}

Vecteur3 Vecteur3::operator*(const float &l) const{
    return Vecteur3(x*l, y*l, z*l);
}

Vecteur3 Vecteur3::operator/(const float &l) const{
    float inv = 1/l;
    return Vecteur3(x*inv, y*inv, z*inv);
}

Vecteur3 Vecteur3::normalize() const{
    float inv = 1/length();
    return Vecteur3(x*inv, y*inv, z*inv);
}

float Vecteur3::scalar(const Vecteur3 &v) const{
    return x*v.x + y*v.y + z*v.z;
}

Vecteur3 Vecteur3::cross(const Vecteur3 &v) const{
    return Vecteur3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}


std::ostream &operator<<(std::ostream &out, Vecteur3 &vect){
    out << "[" << vect.x << ", " << vect.y << ", " << vect.z << "]";
    return out;
}










