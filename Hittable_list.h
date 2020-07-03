#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <tr1/memory>
#include <vector>


using std::shared_ptr;
using std::make_shared;

class Hittable_list: public Hittable
{
    private:
        std::vector<shared_ptr<Hittable>> objs;

    public:
        Hittable_list();
        Hittable_list(shared_ptr<Hittable> obj);

        void clear();
        void add(shared_ptr<Hittable> obj);

        virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &h_rec) const;

};

#endif // HITTABLE_LIST_H
