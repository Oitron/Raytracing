#pragma once

#include "../tools/tools.h"
#include "../Hittable.h"
#include "../math/Vector3.h"


class Material
{
public:
    virtual bool scatter(const Ray& r_incident, const hit_record& h_rec, Vector3& attenuation, Ray& r_scattered) const = 0;
    virtual Vector3 emit() const = 0;
};