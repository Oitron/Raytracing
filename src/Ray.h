#pragma once

#include "math/Vector3.h"


class Ray
{
private:
    Vector3 origin;
    Vector3 direct;

public:
    Ray() : origin(0.0, 0.0, 0.0), direct(0.0, 0.0, 0.0) {}
    Ray(const Vector3& origin_, const Vector3& direct_)
        : origin(origin_), direct(direct_) {}

    Vector3 getOrigin() const { return origin; }
    Vector3 getDirect() const { return direct; }

    Vector3 onto(float& t) const { return origin + direct * t; }
};
