#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "Material.h"


class Lambertian: public Material
{
    private:
        Couleur color_obj;

    public:
        Lambertian();
        Lambertian(const Couleur &color_obj_);

        virtual bool scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const;
        virtual Couleur emit() const;

};

#endif // LAMBERTIAN_H
