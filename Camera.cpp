#include "Camera.h"

Camera::Camera():origin(0.0,0.0,0.0),target(0.0,0.0,1.0),vup(0.0,1.0,0.0),focal_length(1.0),vfov(90.0),aspect_ratio(16.0/9.0)
{}

Camera::Camera(Vecteur3 origin_, Vecteur3 target_, Vecteur3 vup_, float focal_length_, float vfov_, float aspect_ratio_):origin(origin_),target(target_),vup(vup_),focal_length(focal_length_),vfov(vfov_),aspect_ratio(aspect_ratio_)
{}

Ray Camera::get_ray(float a, float b) const{

    Vecteur3 w = (origin-target).normalize();
    Vecteur3 u = (vup.cross(w)).normalize();
    Vecteur3 v = (w.cross(u)).normalize();

    float theta = degree_to_radian(vfov)/2;
    float h = tan(theta)*focal_length;
    float viewport_h = h*2.0;
    float viewport_w = viewport_h*aspect_ratio;

    Vecteur3 horizontal = u*viewport_w;
    Vecteur3 vertical = v*viewport_h;
    Vecteur3 pixel_start = origin - w*focal_length - horizontal/2 + vertical/2; //视窗左上角
    Vecteur3 pixel_current = pixel_start+horizontal*a-vertical*b;
    Vecteur3 direction = pixel_current - origin;
    return Ray(origin, direction);
}
