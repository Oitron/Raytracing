#include "Glass.h"

Glass::Glass():ref_index(1.0)
{}

Glass::Glass(float ref_index_):ref_index(ref_index_)
{}


bool Glass::scatter(const Ray &r_incident, const hit_record &h_rec, Couleur &attenuation, Ray &r_scattered) const{
    attenuation = Couleur(1.0,1.0,1.0);
    float coef;
    if(h_rec.front_side){//�ӿ������벣��
        coef = 1.0/ref_index;
    }
    else{//�Ӳ����������
        coef = ref_index;
    }
    Vecteur3 ray_direct = r_incident.getDirect().normalize();

    float cos_theta = fmin((Vecteur3(0.0,0.0,0.0)-ray_direct).scalar(h_rec.normal),1.0);
    float sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    if(coef*sin_theta > 1.0){//����ȫ����
        Vecteur3 r_reflected = ray_reflect(ray_direct, h_rec.normal);
        r_scattered = Ray(h_rec.p, r_reflected);
        return true;
    }

    float reflect_proba = schlick(cos_theta, coef);
    if(random_real()<reflect_proba){//һ���ֹ��߷�������
        Vecteur3 r_reflected = ray_reflect(ray_direct, h_rec.normal);
        r_scattered = Ray(h_rec.p, r_reflected);
        return true;
    }
    //ʣ����߷�������
    Vecteur3 r_refracted = ray_refract(ray_direct, h_rec.normal, coef);
    r_scattered = Ray(h_rec.p, r_refracted);
    return true;
}

Couleur Glass::emit() const{
    return Couleur(0.0,0.0,0.0);
}
