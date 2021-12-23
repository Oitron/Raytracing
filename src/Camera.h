#pragma once

#include "math/Vector3.h"
#include "tools/tools.h"
#include "Ray.h"

#include <cmath>

class Camera
{
private:
    Vector3 origin; 
    Vector3 target; 
    Vector3 vup; 
    float focal_length; 
    float vfov; 
    float aspect_ratio; 

public:
    Camera() : origin(0.0, 0.0, 0.0), target(0.0, 0.0, 1.0), vup(0.0, 1.0, 0.0), 
               focal_length(1.0), vfov(90.0), aspect_ratio(16.0/9.0){}
    Camera(Vector3 origin_, Vector3 target_, Vector3 vup_,
        float focal_length_, float vfov_, float aspect_ratio_)
        : origin(origin_), target(target_), vup(vup_),
        focal_length(focal_length_), vfov(vfov_), aspect_ratio(aspect_ratio_) {}

    Ray getRay(float a, float b) const {
        Vector3 w = (origin - target).normalize();
        Vector3 u = (vup.cross(w)).normalize();
        Vector3 v = (w.cross(u)).normalize();

        float theta = degree_to_radian(vfov) / 2;
        float h = tan(theta) * focal_length;
        float viewport_h = h * 2.0;
        float viewport_w = viewport_h * aspect_ratio;

        Vector3 horizontal = u * viewport_w;
        Vector3 vertical = v * viewport_h;
        Vector3 pixel_start = origin - w * focal_length - horizontal / 2 + vertical / 2; // ”¥∞◊Û…œΩ«
        Vector3 pixel_current = pixel_start + horizontal * a - vertical * b;
        Vector3 direction = pixel_current - origin;
        return Ray(origin, direction);
    }

};