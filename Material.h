#ifndef MATERIAL_H
#define MATERIAL_H
#include "tools.h"
#include "Hittable.h"
#include "Couleur.h"
#include <tr1/memory>


class Material
{
    public:
        virtual bool scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const = 0;
        virtual Couleur emit() const = 0;
};

#endif // MATERIAL_H
