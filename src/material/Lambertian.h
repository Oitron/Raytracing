#pragma once

#include "Material.h"


class Lambertian : public Material
{
private:
    Vector3 obj_color;

public:
    Lambertian() : obj_color(1.0, 1.0, 1.0) {};
    Lambertian(const Vector3& obj_color_) : obj_color(obj_color_) {}

    virtual bool scatter(const Ray& r_incident, const hit_record& h_rec,
                         Vector3& attenuation, Ray& r_scattered) const {
        Vector3 scatter_at = h_rec.p + h_rec.normal + random_point_on_unit_sphere_surf();
        Vector3 scatter_direct = scatter_at - h_rec.p;
        r_scattered = Ray(h_rec.p, scatter_direct);
        attenuation = obj_color;
        return true;
    }
    virtual Vector3 emit() const { return Vector3(0.0, 0.0, 0.0); }


};