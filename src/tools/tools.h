#pragma once

#include "../math/Vector3.h"
#include <cstdlib>
#include <cmath>


const float PI = 3.1415926535897932385;

inline float degree_to_radian(float degree) {
    return degree * PI / 180;
}

inline float random_real() {
    return rand() / (RAND_MAX + 1.0);
}

inline float random_real(float min_real, float max_real) {
    return min_real + (max_real - min_real) * random_real();
}

inline Vector3 random_vec() {
    return Vector3(random_real(), random_real(), random_real());
}

inline Vector3 random_vec(float min_real, float max_real) {
    return Vector3(random_real(min_real, max_real), random_real(min_real, max_real), random_real(min_real, max_real));
}

inline Vector3 random_point_in_unit_sphere() {
    while (true) {
        Vector3 point = random_vec(-1, 1);
        if (point.length() >= 1) {
            continue;
        }
        return point;
    }
}

inline Vector3 random_point_on_unit_sphere_surf() {
    auto a = random_real(0, 2 * PI);
    auto z = random_real(-1, 1);
    auto r = sqrt(1 - z * z);
    return Vector3(r * cos(a), r * sin(a), z);
}

inline Vector3 ray_reflect(const Vector3& ray, const Vector3 normal) {
    float length = ray.scalar((Vector3(0.0, 0.0, 0.0) - normal)) * 2;
    return ray + normal * (length * 2);
}

inline Vector3 ray_refract(const Vector3& ray, const Vector3 normal, float coef) {
    Vector3 ray_inv = Vector3(0.0, 0.0, 0.0) - ray;
    float rn2 = ray_inv.scalar(normal) * ray_inv.scalar(normal);
    Vector3 parallel = Vector3(0.0, 0.0, 0.0) - normal;
    Vector3 perp = Vector3(0.0, 0.0, 0.0) - ((ray_inv - normal * (normal.scalar(ray_inv))) / sqrt(1 - rn2));
    float parallel_length = sqrt(1 - coef * coef * (1 - rn2));
    float perp_length = coef * sqrt(1 - rn2);
    Vector3 r_ref_parallel = parallel * parallel_length;
    Vector3 r_ref_perp = perp * perp_length;
    return r_ref_parallel + r_ref_perp;
}

inline float schlick(float cosine, float ref_index) {
    float r0 = (1 - ref_index) / (1 + ref_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

