#ifndef LIGHT_H
#define LIGHT_H
#include "Material.h"


class Light: public Material
{
    private:
        Couleur light_color;
    public:
        Light();
        Light(Couleur light_color_);

        virtual bool scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const;
        virtual Couleur emit() const;
};

#endif // LIGHT_H
