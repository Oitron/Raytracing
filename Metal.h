#ifndef METAL_H
#define METAL_H
#include "Material.h"


class Metal: public Material
{
    private:
        Couleur color_obj;
        float matte; //�������������ķ�Χ

    public:
        Metal();
        Metal(const Couleur &color_obj_, float matte_);

        virtual bool scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const;
        virtual Couleur emit() const;

};

#endif // METAL_H
