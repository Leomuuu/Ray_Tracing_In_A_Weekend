#include "HitableList.h"

bool HitableList::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{
	Hit_Record temphit;
	bool hit_anything = false;
	double closet_so_far = t_max;
	for (int i = 0; i < hitables.size(); ++i) {
		if (hitables[i]->Hit(ray, t_min, closet_so_far, temphit)) {
			hit_anything = true;
			closet_so_far = temphit.t;
			hit_record = temphit;
		}
	}
	return hit_anything;
}

void HitableList::AddHitables(HitableObject* object)
{
	hitables.push_back(object);
}