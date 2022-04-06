#include <iostream>
#include <fstream>
#include <limits.h>
#include <float.h>
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
		Vector3 emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.HitPoint);
		if (depth >0 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
			return emitted+attenuation * color(scattered, world, depth + 1);
		}
		return emitted;
		
	}
	else {
		/*Vector3 unit_direction = r.Direction().UnitVector();
		float t = (unit_direction.Y() + 1) * 0.5;
		return Vector3(1, 1, 1)* (1.0 - t) + Vector3(0.5, 0.7, 1.0) * t;*/
		return Vector3(ZEROLIGHT, ZEROLIGHT, ZEROLIGHT);
	}
}


using namespace std;

int main()
{

	ofstream f;
	f.open("test3.ppm");

	srand(time(0));

	int nx = 200;
	int ny = 100;
	int ns = 25;
	f << "P3\n" << nx << " " << ny << "\n255\n";

	HitableObject* List[20];

	Texture* checker = new Checker_Texture(new Constant_Texture(Vector3(0.2, 0.3, 0.1)),
		new Constant_Texture(Vector3(0.9, 0.9, 0.9)));
	Texture* checker4 = new Checker_Texture(new Constant_Texture(Vector3(0.7, 0.2, 0.2)),
		new Constant_Texture(Vector3(0.9, 0.9, 0.9)));
	Texture* checker5 = new Checker_Texture(new Constant_Texture(Vector3(1, 0.84, 0)),
		new Constant_Texture(Vector3(0.9, 0.9, 0.9)));
	Texture* checker2 = new Constant_Texture(Vector3(0.1, 0.1, 0.5));
	Texture* checker3 = new Constant_Texture(Vector3(0.2, 0.2, 0.8));
	Texture* checker6 = new Constant_Texture(Vector3(0.33, 1, 0.62));
	Texture* checker7 = new Constant_Texture(Vector3(0.1, 0, 0));
	Texture* checker8 = new Constant_Texture(Vector3(0, 0.1, 0));
	Texture* checker9 = new Constant_Texture(Vector3(0, 0, 0.1));
	Texture* checker10 = new Constant_Texture(Vector3(0.1, 0.1, 0.1));

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

	List[0] = new Triangle(Vector3(10, -5, 10), Vector3(-10, -5, 10), Vector3(10, -5, -1), new Lambertian(checker7));
	List[1] = new Triangle(Vector3(-10, -5, 10),Vector3(-10, -5, -1), Vector3(10, -5, -1) , new Lambertian(checker7));
	List[2] = new Triangle(Vector3(-10, -5, 10), Vector3(-10, 5, -1),Vector3(-10, -5, -1),new Lambertian(checker8));
	List[3] = new Triangle(Vector3(-10, -5, 10), Vector3(-10, 5, 10), Vector3(-10, 5, -1), new Lambertian(checker8));
	List[4] = new Triangle(Vector3(10, -5, 10),Vector3(10, -5, -1) ,Vector3(10, 5, 10) , new Lambertian(checker9));
	List[5] = new Triangle(Vector3(10, -5, -1), Vector3(10, 5, -1),Vector3(10, 5, 10) , new Lambertian(checker9));
	List[5] = new Triangle(Vector3(10, -5, -1), Vector3(10, 5, -1), Vector3(10, 5, 10), new Lambertian(checker9));
	List[6] = new Triangle(Vector3(10, -5, 10), Vector3(10, 5, 10),Vector3(-10, -5, 10) , new Lambertian(checker10));
	List[7] = new Triangle(Vector3(10, 5, 10),Vector3(-10, -5, 10) ,Vector3(-10, 5, 10), new Lambertian(checker10));
	
	List[8] = new Sphere(Vector3(0, 10, 6), 3, new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))));
	List[9] = new Sphere(Vector3(-8, -3, 8), 1, new Diffuse_Light(new Constant_Texture(Vector3(1, 1, 1))));

	List[10] = new Sphere(Vector3(8, -3, 8), 1, new Lambertian(checker));
	List[11] = new Sphere(Vector3(-5, -3, 8), 2, new Lambertian(checker5));


	HitableList* world = new HitableList();
	world->AddHitables(List[0]);
	world->AddHitables(List[1]);
	world->AddHitables(List[2]);
	world->AddHitables(List[3]);
	world->AddHitables(List[4]);
	world->AddHitables(List[5]);
	world->AddHitables(List[6]);
	world->AddHitables(List[7]);

	world->AddHitables(List[8]);
	world->AddHitables(List[9]);

	world->AddHitables(List[10]);
	world->AddHitables(List[11]);

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

	Vector3 lookfrom(0, 1, -1);
	Vector3 lookat(0, 1, 0);
	/*NormalCamera camera(lookfrom, lookat, Vector3(0, 1, 0), 50,
		double(nx) / double(ny));*/
	DefocusBlurCamera camera(lookfrom, lookat,Vector3(0, 1, 0),90,
		double(nx)/double(ny),0,(lookfrom-lookat).Length());



	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vector3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				for (int z = 0; z < 4; z++) {
					double u = double(double(i)+z*0.25 + RANDDOUBLE01/4) / double(nx);
					double v = double(double(j)+z*0.25 + RANDDOUBLE01/4) / double(ny);
					Ray r = camera.GetRay(u, v);
					Vector3 p = r.Point(2);
					//col = col + color(r, bvhroot, 50);
					col = col + color(r, world, 50);
				}
			}

			col = col / (double(ns)*4);
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


/*
void random_scene(HitableList* world) {
	srand(time(0));
	int i = 1;
	for (int a = -5; a < 5; a++) {
		for (int b = -5; b < 5; b++) {
			auto choose_mat = RANDDOUBLE01;
			Vector3 center(a + 0.9 * RANDDOUBLE01, 0.2, b + 0.9 * RANDDOUBLE01);
			if ((center - Vector3(4, 0.2, 0)).Length() > 0.9) {
				if (choose_mat < 0.8) {
					// diffuse		
					world->AddHitables(new Sphere(center, 0.2,
						new Lambertian(Vector3(RANDDOUBLE01 * RANDDOUBLE01, RANDDOUBLE01 * RANDDOUBLE01, RANDDOUBLE01 * RANDDOUBLE01))));
				}
				else if (choose_mat < 0.95) {
					// metal
					world->AddHitables(new Sphere(center, 0.2,
						new Metal(Vector3(0.5 * (1 + RANDDOUBLE01), 0.5 * (1 + RANDDOUBLE01), 0.5 * (1 + RANDDOUBLE01)), 0.5 * RANDDOUBLE01)));
				}
				else {
					// glass
					world->AddHitables(new Sphere(center, 0.2, new Dielectric(1.5)));
				}
			}
		}
	}

	world->AddHitables(new Sphere(Vector3(0,1,0),1.0, new Dielectric(1.5)));
	world->AddHitables(new Sphere(Vector3(4,1,0), 1.0,
		new Lambertian(Vector3(0.4,0.2,0.1))));
	world->AddHitables(new Sphere(Vector3(-4,1,0), 1.0,
		new Metal(Vector3(0.1,0.6,0.5),0)));

}
*/