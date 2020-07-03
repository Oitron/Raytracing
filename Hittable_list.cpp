#include "Hittable_list.h"

Hittable_list::Hittable_list(){}

Hittable_list::Hittable_list(shared_ptr<Hittable> obj){
    add(obj);
}

void Hittable_list::add(shared_ptr<Hittable> obj){
    objs.push_back(obj);
}

void Hittable_list::clear(){
    objs.clear();
}

bool Hittable_list::hit(const Ray &r, float t_min, float t_max, hit_record &h_rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    float front_cover_back = t_max; //记录当前最近的物体
    for (const shared_ptr<Hittable> &obj : objs){
        if (obj->hit(r, t_min, front_cover_back, temp_rec)){
            front_cover_back = temp_rec.t;
            hit_anything = true;
            h_rec = temp_rec;
        }
    }
    return hit_anything;
}
