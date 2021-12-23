#pragma once

#include "../math/Vector3.h"
#include "../Hittable.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;


class Sphere : public Hittable
{
private:
    Vector3 center;
    float radius;
    shared_ptr<Material> mat_ptr;

public:
    Sphere() : center(0.0, 0.0, -1.0), radius(0.5) {}
    Sphere(Vector3 center_, float radius_, shared_ptr<Material> mat_ptr_)
        : center(center_), radius(radius_), mat_ptr(mat_ptr_) {}

    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& h_rec) const {
        Vector3 oc = r.getOrigin() - center;
        Vector3 ray_direct = r.getDirect();
        float a = ray_direct.scalar(ray_direct);
        float b = 2.0 * oc.scalar(ray_direct);
        float c = oc.scalar(oc) - radius * radius;
        float delta = b * b - 4 * a * c;
        if (delta <= 0) {
            return false;
        }

        float hit_at = (-b - sqrt(delta)) / (2.0 * a);

        if (hit_at < t_max && hit_at > t_min) {
            h_rec.t = hit_at;
            h_rec.p = r.onto(hit_at);
            Vector3 normal_out = (h_rec.p - center).normalize();
            h_rec.set_normal(r, normal_out);
            h_rec.mat_ptr = mat_ptr;
            return true;
        }

        hit_at = (-b + sqrt(delta)) / (2.0 * a);

        if (hit_at < t_max && hit_at > t_min) {
            h_rec.t = hit_at;
            h_rec.p = r.onto(hit_at);
            Vector3 normal_out = (h_rec.p - center).normalize();
            h_rec.set_normal(r, normal_out);
            h_rec.mat_ptr = mat_ptr;
            return true;
        }
        return false;
    }
};
