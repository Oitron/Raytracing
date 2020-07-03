#ifndef SPHERE_H
#define SPHERE_H

#include "Vecteur3.h"
#include "Hittable.h"

using std::shared_ptr;
using std::make_shared;


class Sphere: public Hittable
{
    private:
        Vecteur3 center;
        float radius;
        shared_ptr<Material> mat_ptr;

    public:
        Sphere();
        Sphere(Vecteur3 center_, float radius_, shared_ptr<Material> mat_ptr_);

        virtual bool hit(const Ray &r, float t_min, float t_max, hit_record& h_rec) const;
};

#endif // SPHERE_H
