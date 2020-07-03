#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Vecteur3.h"
#include "Ray.h"
#include "tools.h"


class Camera
{
    private:
        Vecteur3 origin; //相机位置
        Vecteur3 target; //相机视点
        Vecteur3 vup; //相机旋转方向
        float focal_length; //相机焦距
        float vfov; //相机视角（单位为°）
        float aspect_ratio; //相机视区宽高比

    public:
        Camera();
        Camera(Vecteur3 origin_, Vecteur3 target_, Vecteur3 vup_, float focal_length_, float fov_, float aspect_ratio_);

        Ray get_ray(float a, float b) const;

};

#endif // CAMERA_H
