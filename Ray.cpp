#include "Ray.h"

Ray::Ray():origin(0.0,0.0,0.0),direct(0.0,0.0,0.0)
{}

Ray::Ray(const Vecteur3 &origin_, const Vecteur3 &direct_):origin(origin_),direct(direct_)
{}

Vecteur3 Ray::getOrigin() const{
    return origin;
}

Vecteur3 Ray::getDirect() const{
    return direct;
}

Vecteur3 Ray::onto(float &t) const{
    return origin + direct*t;
}


