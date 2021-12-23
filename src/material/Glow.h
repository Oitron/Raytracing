#pragma once

#include "Material.h"


class Glow : public Material
{
private:
    Vector3 glow_color;
public:
    Glow() : glow_color(1.0, 1.0, 1.0) {}
    Glow(Vector3 glow_color_) : glow_color(glow_color_) {}

    virtual bool scatter(const Ray& r_incident, const hit_record& h_rec,
                         Vector3& attenuation, Ray& r_scattered) const {
        return false;
    }

    virtual Vector3 emit() const { return glow_color; }
};
