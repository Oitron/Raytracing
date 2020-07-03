#include "Lambertian.h"

Lambertian::Lambertian():color_obj(1.0,1.0,1.0)
{}

Lambertian::Lambertian(const Couleur &color_obj_):color_obj(color_obj_)
{}

bool Lambertian::scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const{
    Vecteur3 scatter_at = h_rec.p + h_rec.normal + random_point_on_unit_sphere_surf();
    Vecteur3 scatter_direct = scatter_at - h_rec.p;
    r_scattered = Ray(h_rec.p, scatter_direct);
    attenuation = color_obj;
    return true;
}

Couleur Lambertian::emit() const{
    return Couleur(0.0,0.0,0.0);
}
