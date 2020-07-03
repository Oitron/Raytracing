#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Vecteur3.h"
#include "Ray.h"
#include "tools.h"


class Camera
{
    private:
        Vecteur3 origin; //���λ��
        Vecteur3 target; //����ӵ�
        Vecteur3 vup; //�����ת����
        float focal_length; //�������
        float vfov; //����ӽǣ���λΪ�㣩
        float aspect_ratio; //���������߱�

    public:
        Camera();
        Camera(Vecteur3 origin_, Vecteur3 target_, Vecteur3 vup_, float focal_length_, float fov_, float aspect_ratio_);

        Ray get_ray(float a, float b) const;

};

#endif // CAMERA_H
