
Raytracing:main.cpp Vecteur3.o Couleur.o Ray.o Camera.o Sphere.o Hittable_list.o Lambertian.o Metal.o Glass.o Light.o Image.o
	g++ -l pthread -o Raytracing main.cpp Vecteur3.o Couleur.o Ray.o Camera.o Sphere.o Hittable_list.o Lambertian.o Metal.o Glass.o Light.o Image.o
Light.o:Light.cpp
	g++ -c -o Light.o Light.cpp

Glass.o:Glass.cpp
	g++ -c -o Glass.o Glass.cpp

Metal.o:Metal.cpp
	g++ -c -o Metal.o Metal.cpp

Lambertian.o:Lambertian.cpp
	g++ -c -o Lambertian.o Lambertian.cpp

Hittable_list.o:Hittable_list.cpp
	g++ -c -o Hittable_list.o Hittable_list.cpp

Sphere.o:Sphere.cpp
	g++ -c -o Sphere.o Sphere.cpp

Camera.o:Camera.cpp
	g++ -c -o Camera.o Camera.cpp

Ray.o:Ray.cpp
	g++ -c -o Ray.o Ray.cpp

Vecteur3.o:Vecteur3.cpp
	g++ -c -o Vecteur3.o Vecteur3.cpp

Couleur.o:Couleur.cpp
	g++ -c -o Couleur.o Couleur.cpp

Image.o:Image.cpp
	g++ -c -o Image.o Image.cpp

.PHONY: clean
clean :
	rm -rf *.o Raytracing