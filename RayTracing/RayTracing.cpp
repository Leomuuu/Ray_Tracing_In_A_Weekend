#include <iostream>
#include <fstream>
#include <limits.h>
#include <float.h>
#include <algorithm>
#include "Code/Sphere.h"
#include "Code/Cylinder.h"
#include "Code/Triangle.h"
#include "Code/Quadrilateral.h"
#include "Code/HitableList.h"
#include "Code/Vector3.h"
#include "Code/Lambertian.h"
#include "Code/Dielectric.h"
#include "Code/Metal.h"
#include "Code/Camera.h"
#include "Code/Texture.h"
#include "Code/Diffuse_Light.h"
#include "Code/BVHNode.h"
#include "Code/PDF.h"



void random_scene(HitableList* world);

//处理NaN
inline Vector3 DeNaN(const Vector3& vec) {
	Vector3 temp = vec;
	if (isnan(vec.a)) temp.a = 0;
	if (isnan(vec.b)) temp.b = 0;
	if (isnan(vec.c)) temp.c = 0;

	if (isinf(vec.a)) temp.a = 1;
	if (isinf(vec.b)) temp.b = 1;
	if (isinf(vec.c)) temp.c = 1;

	return temp;
}

Vector3 color(Ray r, HitableObject* world,HitableObject* light,int depth) {
	Hit_Record rec;

	if (world->Hit(r, 0.001,FLT_MAX , rec)) {
		Vector3 emitted = rec.mat_ptr->Emitted(r,rec,rec.u, rec.v, rec.HitPoint);
		Scatter_Record srec;
		if (depth >0 && rec.mat_ptr->Scatter(r, rec, srec)) {		
			if (srec.is_specular) {
				return srec.attenuation *
					color(srec.specular_ray, world, light, depth - 1);
			}
			else {
				Cosine_PDF cosp(rec.NormalDirection);
				Hitable_PDF hitp(light, rec.HitPoint);
				Mixture_PDF mixp(&hitp, &cosp, 0.5);
				Ray scattered = Ray(rec.HitPoint, mixp.Generate());
				float pdf = mixp.Value(scattered.Direction());
				return  emitted + srec.attenuation *
					rec.mat_ptr->Scattering_pdf(r, rec, scattered) *
					color(scattered, world, light, depth - 1) / pdf;
			}
		}
		return emitted;
	}
	else {
		return Vector3(ZEROLIGHT, ZEROLIGHT, ZEROLIGHT);
	}
}


using namespace std;

int main()
{

	ofstream f;
	f.open("../Pic/test17 .ppm");

	srand(time(0));

	int nx = 100;
	int ny = 100;
	int ns = 25;
	f << "P3\n" << nx << " " << ny << "\n"<<255<<"\n";

	Texture* red = new Constant_Texture(Vector3(0.65, 0.05, 0.05));
	Texture* green = new Constant_Texture(Vector3(0.12, 0.45, 0.15));
	Texture* yellow = new Constant_Texture(Vector3(1, 0.84, 0));
	Texture* blue= new Constant_Texture(Vector3(0.05,0.05 ,0.65 ));
	Texture* white = new Constant_Texture(Vector3(0.73, 0.73, 0.73));
	Texture* light = new Constant_Texture(Vector3(1, 1, 1));
	Texture* SeaGreen = new Constant_Texture(Vector3(0.33, 1, 0.623));
	Texture* SkyBlue = new Constant_Texture(Vector3(0, 0.75, 1));

	Texture* checker = new Checker_Texture(white ,yellow);

	HitableObject* List[40];

	//left
	List[0] = new Triangle(Vector3(555, 0, 0), Vector3(555, 0, 555), Vector3(555, 555, 0), new Lambertian(green));
	List[1] = new Triangle(Vector3(555, 555, 555), Vector3(555, 0, 555), Vector3(555, 555, 0), new Lambertian(green));
	
	//right
	List[2] = new Triangle(Vector3(0, 0, 0), Vector3(0, 0, 555), Vector3(0, 555, 0), new Lambertian(red));
	List[3] = new Triangle(Vector3(0, 555, 555), Vector3(0, 0, 555), Vector3(0, 555, 0), new Lambertian(red));
	
	//top
	List[4] = new Triangle(Vector3(0, 555, 0), Vector3(0, 555, 555),Vector3(555, 555, 0),new Lambertian(light));
	List[5] = new Triangle(Vector3(555, 555, 555), Vector3(0, 555, 555), Vector3(555, 555, 0), new Lambertian(light));
	
	//bottom
	List[6] = new Triangle(Vector3(0, 0, 0), Vector3(0, 0, 555), Vector3(555, 0, 0), new Lambertian(white));
	List[7] = new Triangle(Vector3(555, 0, 555), Vector3(0, 0, 555), Vector3(555, 0, 0), new Lambertian(white));

	//far
	List[8] = new Triangle(Vector3(0, 0, 555), Vector3(0, 555, 555), Vector3(555, 0, 555), new Lambertian(white));
	List[9] = new Triangle(Vector3(555, 555, 555), Vector3(0, 555, 555), Vector3(555, 0, 555), new Lambertian(white));
	//close
	/*List[10] = new Triangle(Vector3(0, 0, 0), Vector3(0, 555, 0), Vector3(555, 0, 0), new Lambertian(white));
	List[11] = new Triangle(Vector3(555, 555, 0), Vector3(0, 555, 0), Vector3(555, 0, 0), new Lambertian(white));*/

	//left sphere
	List[10] = new Sphere(Vector3(430, 120, 400), 100, new Metal(Vector3(1,1,1),0));

	//mid sphere
	List[11]= new Sphere(Vector3(300, 90, 200), 80, new Lambertian(SkyBlue));
	
	//right sphere
	List[12] = new Sphere(Vector3(180, 90, 80), 100, new Dielectric(0.8));

	////left box
	//List[11] = new Quadrilateral(Vector3(530, 280, 300), Vector3(430, 220, 200),
	//	Vector3(330, 280, 300), Vector3(430, 20, 300),
	//	new Lambertian(SkyBlue));

	////right box
	//List[12] = new Quadrilateral(Vector3(292, 52, 142), Vector3(153, 42, 100),
	//	Vector3(43, 72, 435), Vector3(222, 164, 188),
	//	new Lambertian(SeaGreen));

	//light
	List[13] = new Cylinder(280, 280, 150, 554.9999, 554.9999, new Diffuse_Light(light), new Diffuse_Light(light));
	/*List[13] = new Triangle(Vector3(280, 483, 150), Vector3(180, 483, 380), Vector3(380, 483, 380),
		new Diffuse_Light(light));
	List[14] = new Triangle(Vector3(280, 403, 400), Vector3(180, 483, 380), Vector3(380, 483, 380),
		new Diffuse_Light(light));
	List[15] = new Triangle(Vector3(280, 483, 150), Vector3(280, 403, 400), Vector3(380, 483, 380),
		new Diffuse_Light(light));
	List[16] = new Triangle(Vector3(280, 483, 150), Vector3(180, 483, 380), Vector3(280, 403, 400),
		new Diffuse_Light(light));*/
	

	HitableList* world = new HitableList();
	HitableList* worldlight = new HitableList();
	for (int i = 0; i < 13; i++) {
		world->AddHitables(List[i]);
	}
	for (int i = 13; i < 14; i++) {
		worldlight->AddHitables(List[i]);
	}
	worldlight->AddHitables(List[12]);

	world->AddHitables(worldlight);

	//BVHNode* bvhroot = new BVHNode(world);
	
	Vector3 lookfrom(278, 278, -800);
	Vector3 lookat(278, 278, 0);

	DefocusBlurCamera camera(lookfrom, lookat,Vector3(0, 1, 0),40,
		float(nx)/float(ny),0,5);



	for (int j = ny - 1; j >= 0; j--) {
	/*for (int j = 0; j <=ny-1; j++) {*/
		for (int i = 0; i < nx; i++) {
			Vector3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				for (int z = 0; z < 4; z++) {
					float u = float(float(i)+z*0.25 + RANDfloat01/4) / float(nx);
					float v = float(float(j)+z*0.25 + RANDfloat01/4) / float(ny);
					Ray r = camera.GetRay(u, v);
					Vector3 p = r.Point(2);
					//col = col + color(r, bvhroot, 10);
					col = col + DeNaN(color(r, world,worldlight,5));
				}
			}

			col = col / (float(ns)*4);
			col = Vector3(sqrt(col.R()), sqrt(col.G()), sqrt(col.B()));

			int ir = int(255.99 * col.R());
			int ig = int(255.99 * col.G());
			int ib = int(255.99 * col.B());

			cout << j <<" "<<i<<endl;

			f << ir << " " << ig << " " << ib << "\n";
		}
	}
	f.close();
}

