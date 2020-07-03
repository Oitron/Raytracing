#ifndef RAY_H
#define RAY_H
#include "Vecteur3.h"


class Ray
{
    private:
        Vecteur3 origin; //�����
        Vecteur3 direct; //����

    public:
        Ray();
        Ray(const Vecteur3 &origin_, const Vecteur3 &direct_);

        Vecteur3 getOrigin() const; //��ȡ�����
        Vecteur3 getDirect() const; //��ȡ����

        Vecteur3 onto(float &t) const;
};

#endif // RAY_H
