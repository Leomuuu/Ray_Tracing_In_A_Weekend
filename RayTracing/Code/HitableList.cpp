#include "HitableList.h"

bool HitableList::Hit(Ray& ray, float t_min, float t_max, Hit_Record& hit_record)
{
	Hit_Record temphit;
	bool hit_anything = false;
	float closet_so_far = t_max;
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

bool HitableList::BoundingBox(float t0, float t1, AABB& aabb)
{
	if (hitables.size() < 1) return false;

	AABB tempbox;
	bool firsttrue = hitables[0]->BoundingBox(t0, t1, tempbox);
	if (!firsttrue) return false;
	aabb = tempbox;

	for (int i = 1; i < hitables.size(); ++i) {
		if (hitables[i]->BoundingBox(t0, t1, tempbox)) {
			aabb = aabb.SurroundingBox(tempbox);
		}
		else return false;
	}

	return true;

}