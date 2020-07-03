#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <vector>
#include <future>
#include <string.h>
#include <atomic>

#include "Couleur.h"
#include "Vecteur3.h"
#include "Image.h"
#include "Ray.h"
#include "Hittable_list.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Glass.h"
#include "Light.h"
#include "tools.h"
#include "svpng.inc"



using namespace std;
using std::shared_ptr;
using std::make_shared;
const double infinity = numeric_limits<double>::infinity();




Couleur ray_couleur(const Ray &r, const Hittable &object, int max_iter){
    hit_record h_rec;

    if(max_iter <= 0){
        return Couleur(0.0,0.0,0.0);
    }
    float t_min = 0.0001;
    float t_max = infinity;
    if(object.hit(r,t_min,t_max,h_rec)){
        Ray r_scattered;
        Couleur attenuation;
        Couleur emitted = h_rec.mat_ptr->emit();

        if(!h_rec.mat_ptr->scatter(r, h_rec, attenuation, r_scattered)){
            return emitted;
        }
        return emitted + attenuation * ray_couleur(r_scattered, object, max_iter-1);
    }
    return Couleur(0.0,0.0,0.0);
}

string each_thread(int thread, int cpt_start, int cpt_end, int img_w, int img_h, int pixel_samples, int max_iter, Camera cam, const Hittable &object, unsigned char *img){
    int cpt = cpt_start*img_w*3;
    int pixel = 0;
    for (int i=cpt_start; i<cpt_end; ++i){
        for (int j=0; j<img_w; ++j){
            Couleur pixel_couleur(0.0,0.0,0.0);
            for (int s=0; s<pixel_samples; ++s){ //�����
                float u = (float(j)+random_real())/(img_w-1);
                float v = (float(i)+random_real())/(img_h-1);
                Ray r = cam.get_ray(u,v);
                pixel_couleur = pixel_couleur + ray_couleur(r,object,max_iter);
            }
            pixel_couleur = pixel_couleur/pixel_samples;
            float pixel_r = sqrt(pixel_couleur.getR())*255.0;//٤���޸�
            float pixel_g = sqrt(pixel_couleur.getG())*255.0;
            float pixel_b = sqrt(pixel_couleur.getB())*255.0;
            img[cpt] = pixel_r;
            cpt++;
            img[cpt] = pixel_g;
            cpt++;
            img[cpt] = pixel_b;
            cpt++;
            pixel++;

            cerr << "\r " << std::flush;
            //float progress = float(pixel)/float((cpt_end-cpt_start)*img_w-1)*100;
            //cerr.setf(ios::fixed);
            //cerr << setprecision(2);
            //cerr <<  "\rRendering: " << progress << "% "  << std::flush;
        }
    }
    string output_info = "Part " + to_string(thread+1) + " done.";
    return output_info;
}


int main()
{
/*
    int size = 512 << 20; // 512MB //����ջ�Ĵ�С�����������ܴ�ʱ���õ�
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
*/
    string path = "./output/scene_02.png";

    const float aspect_ratio = 16.0/9.0;
    const int img_w = 640;
    const int img_h = static_cast<int>(img_w/aspect_ratio);
    const int pixel_samples = 100;
    const int max_iter = 100;

    float vfov = 45.0;
    //float viewport_w = viewport_h*aspect_ratio;
    float focal_length = 1.0;
    Vecteur3 origin(-1.5,0.5,3.5);
    Vecteur3 target(0.0,-0.4,-2.0);
    Vecteur3 vup(0.0,1.0,0.0);

    Camera cam(origin, target, vup, focal_length, vfov, aspect_ratio);
/*
    Vecteur3 origin = Vecteur3(0.0,0.0,0.0);
    Vecteur3 horizontal = Vecteur3(viewport_w,0.0,0.0);
    Vecteur3 vertical = Vecteur3(0.0,viewport_h,0.0);
    Vecteur3 pixel_start = Vecteur3(-viewport_w/2, viewport_h/2,-focal_length);//�ӿ����Ͻ�
*/

    /*��������*/
    Hittable_list objects;

    objects.add(make_shared<Sphere>(Vecteur3(30,75,0.0),50.0,make_shared<Light>(Couleur(1.0,1.0,1.0))));//�ƹ�
    //objects.add(make_shared<Sphere>(Vecteur3(0.0,3.0,-0.5),1.3,make_shared<Light>(Couleur(1.0,1.0,1.0))));//�ƹ�
    objects.add(make_shared<Sphere>(Vecteur3(0.0,-0.3,-2.5),0.2,make_shared<Lambertian>(Couleur(0.7,0.3,0.3))));//����
    objects.add(make_shared<Sphere>(Vecteur3(0.8,-0.2,-3.0),0.3,make_shared<Lambertian>(Couleur(0.7,0.8,0.3))));//����
    objects.add(make_shared<Sphere>(Vecteur3(1.5,-0.3,-3.5),0.2,make_shared<Metal>(Couleur(0.7,0.3,0.9),0.0)));//����
    objects.add(make_shared<Sphere>(Vecteur3(-0.5,-0.3,-4.5),0.2,make_shared<Lambertian>(Couleur(0.2,0.5,0.3))));//����
    objects.add(make_shared<Sphere>(Vecteur3(0.0,-800.5,-1.0),800.0,make_shared<Lambertian>(Couleur(0.5,0.5,0.5))));//����
    objects.add(make_shared<Sphere>(Vecteur3(250.0,-100.0,-1600.0),1000.0,make_shared<Lambertian>(Couleur(0.9,0.9,0.9))));//����
    objects.add(make_shared<Sphere>(Vecteur3(1.3,0.0,-0.6),0.5,make_shared<Metal>(Couleur(0.8,0.6,0.2),0.2)));
    //objects.add(make_shared<Sphere>(Vecteur3(0.0,0.0,-2.0),0.5,make_shared<Metal>(Couleur(0.7,0.8,0.7),0.0)));
    objects.add(make_shared<Sphere>(Vecteur3(-1.6,0.0,-0.3),0.5,make_shared<Metal>(Couleur(0.3,0.2,0.7),0.0)));
    objects.add(make_shared<Sphere>(Vecteur3(0.0,0.3,-1.0),0.8,make_shared<Glass>(1.5)));
    objects.add(make_shared<Sphere>(Vecteur3(-0.5,-0.3,1.3),0.2,make_shared<Glass>(1.3)));
    objects.add(make_shared<Sphere>(Vecteur3(0.6,-0.35,0.5),0.15,make_shared<Glass>(2.0)));
    objects.add(make_shared<Sphere>(Vecteur3(-0.2,-0.4,1.5),0.1,make_shared<Lambertian>(Couleur(0.7,0.1,0.3))));//����
    objects.add(make_shared<Sphere>(Vecteur3(-0.6,-0.2,0.5),0.3,make_shared<Metal>(Couleur(0.3,0.8,0.2),0.2)));
    //objects.add(make_shared<Sphere>(Vecteur3(-1.0,1.0,-1.0),0.45,make_shared<Glass>(1.7)));
    //objects.add(make_shared<Sphere>(Vecteur3(-1.0,0.0,-2.0),0.5,make_shared<Lambertian>(Couleur(0.3,0.3,0.8))));


    int thread_num = 0;
    cout << "The number of render threads: ";
    cin >> thread_num;

    const char* file_path = path.c_str();
    cout << "\rStart rendering file: " << file_path << endl;

    if(thread_num == 0){
        thread_num = 1;
    }

    unsigned char img_output[img_h*img_w*3] = {0};

    int img_h_part = int(img_h/thread_num);
    int img_h_part_last = img_h - img_h_part*(thread_num-1);

    vector<future<string>> threads;

    //int pixel = 0;
    for(int t=0; t<thread_num; t++){
        int cpt_start = t*img_h_part;
        int cpt_end = cpt_start+img_h_part;
        if(t == thread_num-1){
            cpt_end = cpt_start+img_h_part_last;
        }
        threads.emplace_back(async(std::launch::async, each_thread, t, cpt_start, cpt_end, img_w, img_h, pixel_samples, max_iter, cam, objects, img_output));
    }

    //��ʼ��Ⱦ
    for (future<string> &thread : threads) {
        cout << thread.get() << endl;
    }

    /*���PPM
    Image img_PPM(img_w, img_h, 255, img_output);
    std::ofstream outFile;
    outFile.open("C:\\Users\\ME\\Desktop\\test_bg43.ppm", std::ios::binary);
    outFile << img_PPM;
    outFile.clear();
    outFile.close();
    */
    FILE *fp = fopen(file_path, "wb");
    svpng(fp, img_w, img_h, img_output, 0);
    fclose(fp);

    cout << endl << "Rendering complete!" << endl;

    return 0;
}
