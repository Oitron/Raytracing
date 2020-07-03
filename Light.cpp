#include "Light.h"

Light::Light():light_color(1.0,1.0,1.0)
{}

Light::Light(Couleur light_color_):light_color(light_color_)
{}

bool Light::scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const{
    return false;
}

Couleur Light::emit() const{
    return light_color;
}
