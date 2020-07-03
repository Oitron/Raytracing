#ifndef GLASS_H
#define GLASS_H
#include "Material.h"

class Glass: public Material
{
    private:
        float ref_index;

    public:
        Glass();
        Glass(float ref_index_);

        virtual bool scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const;
        virtual Couleur emit() const;
};

#endif // GLASS_H
