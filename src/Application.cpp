#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <vector>
#include <future>
#include <string>
#include <atomic>
#include <Thread>
#include <Windows.h>
#include <malloc.h>

#include "math/Vector3.h"
#include "Ray.h"
#include "HittableList.h"
#include "model/Sphere.h"
#include "Camera.h"
#include "material/Material.h"
#include "material/Metal.h"
#include "material/Glass.h"
#include "material/Lambertian.h"
#include "material/Glow.h"
#include "tools/tools.h"
#include "output/Image.h"
#include "vendor/output_image/svpng.inc"

#pragma comment(linker, "/STACK:1073741824") //加大堆栈大小


using namespace std;
using std::shared_ptr;
using std::make_shared;
const double infinity = numeric_limits<double>::infinity();

#define NB_CHANNEL 3


Vector3 rayColor(const Ray& r, const Hittable& object, int max_iter) {
    hit_record h_rec;

    if (max_iter <= 0) {
        return Vector3(0.0, 0.0, 0.0);
    }
    float t_min = 0.0001;
    float t_max = infinity;
    if (object.hit(r, t_min, t_max, h_rec)) {
        Ray r_scattered;
        Vector3 attenuation;
        Vector3 emitted = h_rec.mat_ptr->emit();

        if (!h_rec.mat_ptr->scatter(r, h_rec, attenuation, r_scattered)) {
            return emitted;
        }
        return emitted + attenuation * rayColor(r_scattered, object, max_iter - 1);
    }
    return Vector3(0.0, 0.0, 0.0);
}

string each_thread(int thread, int cpt_start, int cpt_end, int img_w, int img_h, int pixel_samples, int max_iter, Camera cam, const Hittable& object, unsigned char* img) {
    int cpt = cpt_start * img_w * 3;
    int pixel = 0;
    for (int i = cpt_start; i < cpt_end; ++i) {
        for (int j = 0; j < img_w; ++j) {
            Vector3 pixel_Vector3(0.0, 0.0, 0.0);
            for (int s = 0; s < pixel_samples; ++s) {
                float u = (float(j) + random_real()) / (img_w - 1);
                float v = (float(i) + random_real()) / (img_h - 1);
                Ray r = cam.getRay(u, v);
                pixel_Vector3 = pixel_Vector3 + rayColor(r, object, max_iter);
            }
            pixel_Vector3 = pixel_Vector3 / pixel_samples;
            float pixel_r = sqrt(pixel_Vector3.getX()) * 255.0;
            float pixel_g = sqrt(pixel_Vector3.getY()) * 255.0;
            float pixel_b = sqrt(pixel_Vector3.getZ()) * 255.0;
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
    string output_info = "Part " + to_string(thread + 1) + " done.";
    return output_info;
}


int main()
{
    /*
    int size = 512 << 20; // 512MB //定义栈的大小，迭代次数很大时会用到
    char* p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
    */

    string path = "F:\\M2\\IG3DA\\RayTracing\\PathTracing\\output\\scene_02.ppm";

    const int img_w = 640;
    const int img_h = 360;
    const float aspect_ratio = 16.0 / 9.0;
    const int pixel_samples = 500;
    const int max_iter = 500;

    float vfov = 45.0;
    //float viewport_w = viewport_h*aspect_ratio;
    float focal_length = 1.0;
    Vector3 origin(-1.5, 0.5, 3.5);
    Vector3 target(0.0, -0.4, -2.0);
    Vector3 vup(0.0, 1.0, 0.0);

    Camera cam(origin, target, vup, focal_length, vfov, aspect_ratio);
    /*
        Vecteur3 origin = Vecteur3(0.0,0.0,0.0);
        Vecteur3 horizontal = Vecteur3(viewport_w,0.0,0.0);
        Vecteur3 vertical = Vecteur3(0.0,viewport_h,0.0);
        Vecteur3 pixel_start = Vecteur3(-viewport_w/2, viewport_h/2,-focal_length);
    */

    HittableList objects;

    objects.add(make_shared<Sphere>(Vector3(30, 75, 0.0), 50.0, make_shared<Glow>(Vector3(1.0, 1.0, 1.0))));
    //objects.add(make_shared<Sphere>(Vecteur3(0.0,3.0,-0.5),1.3,make_shared<Light>(Vector3(1.0,1.0,1.0))));
    objects.add(make_shared<Sphere>(Vector3(0.0, -0.3, -2.5), 0.2, make_shared<Lambertian>(Vector3(0.7, 0.3, 0.3))));
    objects.add(make_shared<Sphere>(Vector3(0.8, -0.2, -3.0), 0.3, make_shared<Lambertian>(Vector3(0.7, 0.8, 0.3))));
    objects.add(make_shared<Sphere>(Vector3(1.5, -0.3, -3.5), 0.2, make_shared<Metal>(Vector3(0.7, 0.3, 0.9), 0.0)));
    objects.add(make_shared<Sphere>(Vector3(-0.5, -0.3, -4.5), 0.2, make_shared<Lambertian>(Vector3(0.2, 0.5, 0.3))));
    objects.add(make_shared<Sphere>(Vector3(0.0, -800.5, -1.0), 800.0, make_shared<Lambertian>(Vector3(0.5, 0.5, 0.5))));
    objects.add(make_shared<Sphere>(Vector3(250.0, -100.0, -1600.0), 1000.0, make_shared<Lambertian>(Vector3(0.9, 0.9, 0.9))));
    objects.add(make_shared<Sphere>(Vector3(1.3, 0.0, -0.6), 0.5, make_shared<Metal>(Vector3(0.8, 0.6, 0.2), 0.2)));
    //objects.add(make_shared<Sphere>(Vecteur3(0.0,0.0,-2.0),0.5,make_shared<Metal>(Vector3(0.7,0.8,0.7),0.0)));
    objects.add(make_shared<Sphere>(Vector3(-1.6, 0.0, -0.3), 0.5, make_shared<Metal>(Vector3(0.3, 0.2, 0.7), 0.0)));
    objects.add(make_shared<Sphere>(Vector3(0.0, 0.3, -1.0), 0.8, make_shared<Glass>(1.5)));
    objects.add(make_shared<Sphere>(Vector3(-0.5, -0.3, 1.3), 0.2, make_shared<Glass>(1.3)));
    objects.add(make_shared<Sphere>(Vector3(0.6, -0.35, 0.5), 0.15, make_shared<Glass>(2.0)));
    objects.add(make_shared<Sphere>(Vector3(-0.2, -0.4, 1.5), 0.1, make_shared<Lambertian>(Vector3(0.7, 0.1, 0.3))));
    objects.add(make_shared<Sphere>(Vector3(-0.6, -0.2, 0.5), 0.3, make_shared<Metal>(Vector3(0.3, 0.8, 0.2), 0.2)));
    //objects.add(make_shared<Sphere>(Vecteur3(-1.0,1.0,-1.0),0.45,make_shared<Glass>(1.7)));
    //objects.add(make_shared<Sphere>(Vecteur3(-1.0,0.0,-2.0),0.5,make_shared<Lambertian>(Vector3(0.3,0.3,0.8))));


    int thread_num = 0;
    cout << "The number of render threads: ";
    cin >> thread_num;

    const char* file_path = path.c_str();
    cout << "\rStart rendering file: " << file_path << endl;

    if (thread_num == 0) {
        thread_num = 1;
    }

    unsigned char* img_output;
    img_output = (unsigned char *) malloc(img_h * img_w * NB_CHANNEL);

    int img_h_part = int(img_h / thread_num);
    int img_h_part_last = img_h - img_h_part * (thread_num - 1);

    vector<future<string>> threads;

    //int pixel = 0;
    for (int t = 0; t < thread_num; t++) {
        int cpt_start = t * img_h_part;
        int cpt_end = cpt_start + img_h_part;
        if (t == thread_num - 1) {
            cpt_end = cpt_start + img_h_part_last;
        }
        threads.emplace_back(std::async(std::launch::async, each_thread, t, cpt_start, cpt_end, img_w, img_h,
                                                pixel_samples, max_iter, cam, objects, img_output));
    }

    for (future<string>& thread : threads) {
        cout << thread.get() << endl;
    }

    
    Image img_PPM(img_w, img_h, 255, img_output);
    std::ofstream outFile;
    outFile.open(file_path, std::ios::binary);
    outFile << img_PPM;
    outFile.clear();
    outFile.close();

    /*
    FILE* fp = fopen(file_path, "wb");
    svpng(fp, img_w, img_h, img_output, 0);
    fclose(fp);
    */
    cout << endl << "Rendering complete!" << endl;

    return 0;
}
