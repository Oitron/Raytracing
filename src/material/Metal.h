#pragma once

#include "Material.h"


class Metal : public Material
{
private:
    Vector3 obj_color;
    float matte; 

public:
    Metal() : obj_color(1.0, 1.0, 1.0), matte(0.0) {}
    Metal(const Vector3& obj_color_, float matte_) : obj_color(obj_color_), matte(matte_) {}

    virtual bool scatter(const Ray& r_incident, const hit_record& h_rec, 
                         Vector3& attenuation, Ray& r_scattered) const {
        Vector3 r_reflected = ray_reflect(r_incident.getDirect().normalize(), h_rec.normal);
        r_scattered = Ray(h_rec.p, r_reflected + random_point_in_unit_sphere() * matte);
        attenuation = obj_color;
        return r_reflected.scalar(h_rec.normal) > 0;
    }
    virtual Vector3 emit() const {
        return Vector3(0.0, 0.0, 0.0);
    }

};