#include "Quadrilateral.h"

bool Quadrilateral::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{
	Triangle* trilist[4] = { new Triangle(point1,point2,point3,material),new Triangle(point1,point2,point4,material),
		new Triangle(point1,point3,point4,material),new Triangle(point2,point3,point4,material),
	};

	bool hit_anything = false;

	double t = t_max;
	for (int i = 0; i < 4; i++) {
		if (trilist[i]->Hit(ray, t_min, t_max, hit_record)) {
			t_max = hit_record.t;
			hit_anything = true;
		}
	}

	return hit_anything;

}