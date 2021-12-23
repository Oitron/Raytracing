#pragma once

#include "Material.h"


class Glass : public Material
{
private:
    float ref_index;

public:
    Glass() : ref_index(1.0) {}
    Glass(float ref_index_) : ref_index(ref_index_) {}

    virtual bool scatter(const Ray& r_incident, const hit_record& h_rec,
                         Vector3& attenuation, Ray& r_scattered) const {
        attenuation = Vector3(1.0, 1.0, 1.0);
        float coef;
        if (h_rec.front_side) {
            coef = 1.0 / ref_index;
        }
        else {
            coef = ref_index;
        }
        Vector3 ray_direct = r_incident.getDirect().normalize();

        float cos_theta = fmin((Vector3(0.0, 0.0, 0.0) - ray_direct).scalar(h_rec.normal), 1.0);
        float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        if (coef * sin_theta > 1.0) {
            Vector3 r_reflected = ray_reflect(ray_direct, h_rec.normal);
            r_scattered = Ray(h_rec.p, r_reflected);
            return true;
        }

        float reflect_proba = schlick(cos_theta, coef);
        if (random_real() < reflect_proba) {
            Vector3 r_reflected = ray_reflect(ray_direct, h_rec.normal);
            r_scattered = Ray(h_rec.p, r_reflected);
            return true;
        }

        Vector3 r_refracted = ray_refract(ray_direct, h_rec.normal, coef);
        r_scattered = Ray(h_rec.p, r_refracted);
        return true;
    }

    virtual Vector3 emit() const { return Vector3(0.0, 0.0, 0.0); }
};