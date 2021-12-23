#pragma once

#include "Hittable.h"

#include <vector>


using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
private:
    std::vector<shared_ptr<Hittable>> objs;

public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> obj) { add(obj); }

    void clear() { objs.clear(); }
    void add(shared_ptr<Hittable> obj) { objs.push_back(obj); }

    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& h_rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        float front_cover_back = t_max;
        for (const shared_ptr<Hittable>& obj : objs) {
            if (obj->hit(r, t_min, front_cover_back, temp_rec)) {
                front_cover_back = temp_rec.t;
                hit_anything = true;
                h_rec = temp_rec;
            }
        }
        return hit_anything;
    }

};