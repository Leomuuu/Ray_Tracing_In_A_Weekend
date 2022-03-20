#include <iostream>
#include <fstream>
#include <limits.h>
#include <float.h>
#include "Code/Sphere.h"
#include "Code/HitableList.h"
#include "Code/Vector3.h"



Vector3 color(Ray& r, HitableObject* world) {
	Hit_Record rec;

	if (world->Hit(r, 0.0,FLT_MAX , rec)) {
		return Vector3(rec.NormalDirection.X() + 1,
			rec.NormalDirection.Y() + 1, rec.NormalDirection.Z() + 1)*0.5;
	}
	else {
		Vector3 unit_direction = r.Direction().NormalNize();
		float t = (unit_direction.Y() + 1) * 0.5;
		return Vector3(1, 1, 1)* (1 - t) + Vector3(0.5, 0.7, 1.0) * t;
	}
}


using namespace std;

int main()
{
	ofstream f;
	f.open("test.ppm");

	int nx = 200;
	int ny = 100;
	f << "P3\n" << nx << " " << ny << "\n255\n";

	Vector3 lower_left_corner(-2.0, -1.0, -1.0);
	Vector3 horizontal(4.0, 0.0, 0.0);
	Vector3 vertical(0, 2, 0);
	Vector3 origin(0, 0, 0);

	HitableObject* List[2];

	List[0] = new Sphere(Vector3(0, 0, -1), 0.5);
	List[1] = new Sphere(Vector3(0, -100.5, -1), 100);

	HitableList* world = new HitableList();
	world->AddHitables(List[0]);
	world->AddHitables(List[1]);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			double u = double(i) / double(nx);
			double v= double(j) / double(ny);

			Ray r(origin, lower_left_corner + horizontal * u + vertical * v);

			Vector3 p = r.Point(2);
			Vector3 col = color(r, world);

			int ir = int(255.99 * col.R());
			int ig = int(255.99 * col.G());
			int ib = int(255.99 * col.B());

			f << ir << " " << ig << " " << ib << "\n";
		}
	}




	f.close();
}
