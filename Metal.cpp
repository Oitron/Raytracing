#include "Metal.h"

Metal::Metal():color_obj(1.0,1.0,1.0),matte(0.0)
{}

Metal::Metal(const Couleur &color_obj_, float matte_):color_obj(color_obj_),matte(matte_)
{}

bool Metal::scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const{
    Vecteur3 r_reflected = ray_reflect(r_incident.getDirect().normalize(), h_rec.normal);
    r_scattered = Ray(h_rec.p, r_reflected + random_point_in_unit_sphere()*matte);
    attenuation = color_obj;
    return r_reflected.scalar(h_rec.normal) > 0;
}

Couleur Metal::emit() const{
    return Couleur(0.0,0.0,0.0);
}
