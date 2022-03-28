#include "Quadrilateral.h"

bool Quadrilateral::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{

	bool hit_anything = false;

	double t = t_max;
	for (int i = 0; i < 4; i++) {
		if (trilist[i].Hit(ray, t_min, t_max, hit_record)) {
			t_max = hit_record.t;
			hit_anything = true;
		}
	}

	return hit_anything;

}