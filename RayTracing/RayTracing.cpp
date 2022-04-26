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



void random_scene(HitableList* world);

Vector3 color(Ray r, HitableObject* world,int depth) {
	Hit_Record rec;

	if (world->Hit(r, 0.001,FLT_MAX , rec)) {
		Ray scattered;
		Vector3 attenuation;
		Vector3 direclight;
		Vector3 emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.HitPoint);
		if (depth >0 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
			Vector3 ret;
			
			ret =  attenuation * color(scattered, world, depth - 1);		
			
			return ret+emitted;
		}
		
		return emitted;
		
	}
	else {
		/*Vector3 unit_direction = r.Direction().UnitVector();
		float t = (unit_direction.Y() + 1) * 0.5;
		return Vector3(1, 1, 1)* (1.0 - t) + Vector3(0.5, 0.7, 1.0) * t;*/
		return Vector3(ZEROLIGHT, ZEROLIGHT, ZEROLIGHT);
		//return Vector3(1, 1, 1);
	}
}


using namespace std;

int main()
{

	ofstream f;
	f.open("test5.ppm");

	srand(time(0));

	int nx = 100;
	int ny = 100;
	int ns = 5;
	f << "P3\n" << nx << " " << ny << "\n255\n";

	HitableObject* List[22];

	Texture* red = new Constant_Texture(Vector3(0.65, 0.05, 0.05));
	Texture* green = new Constant_Texture(Vector3(0.12, 0.45, 0.15));
	Texture* yellow = new Constant_Texture(Vector3(1, 0.84, 0));
	Texture* white = new Constant_Texture(Vector3(0.73, 0.73, 0.73));
	Texture* light = new Constant_Texture(Vector3(1, 1, 1));

	Texture* checker = new Checker_Texture(white ,yellow);


	/*List[1]= new Sphere(Vector3(2, 1.5, 1), 0.5, new Lambertian(checker));
	List[2] = new Sphere(Vector3(1, 1.5, 1), 0.2, new Metal(Vector3(0.5, 0.2, 0.5), 0));

	List[3] = new Triangle(Vector3(-0.5, 0.5, 1), Vector3(-1.5, 2, 2.5), Vector3(-2.5, 0.5, 1), new Lambertian(checker6));
	List[4] = new Triangle(Vector3(-0.5, 0.5, 1), Vector3(-1.2, 1, 1), Vector3(-1.5, 2, 2.5), new Lambertian(checker8));

	List[5] = new Quadrilateral(Vector3(-0.5, 0.5, 1), Vector3(-1.5, 2, 2.5), Vector3(-2.5, 0.5, 1), Vector3(-1.2, 1, 1),
		new Lambertian(checker6));

	List[10] = new Cylinder(2, 0, 0.2, -1.1, -1.1, new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))),
		new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))));
	List[11] = new Cylinder(0, 1, 1, -1.5, -0.5, new Lambertian(checker2), new Lambertian(checker3));

	List[12]= new Sphere(Vector3(0, 3.5, 1), 1.5, new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))));
	List[13] = new Sphere(Vector3(3, 0, 1), 1, new Metal(Vector3(0.5, 0.5, 0.5), 0));
	List[14] = new Sphere(Vector3(2, -1, 0), 0.3, new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))));
	List[15] = new Sphere(Vector3(-3, -1, 1), 1, new Lambertian(checker4));
	List[16] = new Sphere(Vector3(0, -104, 1), 100, new Lambertian(checker5));
	List[17] = new Sphere(Vector3(-1.2, 1.5, 0), 0.5, new Dielectric(0.9));*/

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

	//light
	List[10] = new Cylinder(280, 280, 65, 555, 555, new Diffuse_Light(white), new Diffuse_Light(white));

	//left sphere
	List[11] = new Sphere(Vector3(400, 100, 400), 70, new Lambertian(checker));

	HitableList* world = new HitableList();
	for (int i = 0; i < 12; i++) {
		world->AddHitables(List[i]);
	}


	//world->AddHitables(List[1]);
	//world->AddHitables(List[2]);
	//world->AddHitables(List[5]);
	//world->AddHitables(List[11]);
	//world->AddHitables(List[12]);
	//world->AddHitables(List[13]);
	//world->AddHitables(List[10]);
	//world->AddHitables(List[15]);
	//world->AddHitables(List[16]);
	//world->AddHitables(List[17]);
	//random_scene(world);

	BVHNode* bvhroot = new BVHNode(world);
	
	Vector3 lookfrom(278, 278, -800);
	Vector3 lookat(278, 278, 0);
	/*NormalCamera camera(lookfrom, lookat, Vector3(0, 1, 0), 40,
		float(nx) / float(ny));*/
	DefocusBlurCamera camera(lookfrom, lookat,Vector3(0, 1, 0),40,
		float(nx)/float(ny),0,10);



	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vector3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				for (int z = 0; z < 4; z++) {
					float u = float(float(i)+z*0.25 + RANDfloat01/4) / float(nx);
					float v = float(float(j)+z*0.25 + RANDfloat01/4) / float(ny);
					Ray r = camera.GetRay(u, v);
					Vector3 p = r.Point(2);
					//col = col + color(r, bvhroot, 10);
					col = col + color(r, world, 10);
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

