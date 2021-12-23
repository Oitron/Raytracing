#pragma once

#include "Ray.h"
#include <memory>

using namespace std;
using std::shared_ptr;
using std::make_shared;
class Material;


struct hit_record {
    Vector3 p;
    Vector3 normal;
    float t;
    bool front_side;
    shared_ptr<Material> mat_ptr;

    inline void set_normal(const Ray& r, const Vector3 normal_out) {
        front_side = (r.getDirect().scalar(normal_out)) < 0;
        if (front_side) {
            normal = normal_out;
        }
        else {
            normal = Vector3(0.0, 0.0, 0.0) - normal_out;
        }
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& h_rec) const = 0;
};