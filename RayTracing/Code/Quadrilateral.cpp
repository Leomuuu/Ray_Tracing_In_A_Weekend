#include "Quadrilateral.h"

bool Quadrilateral::Hit(Ray& ray, float t_min, float t_max, Hit_Record& hit_record)
{

	bool hit_anything = false;

	float t = t_max;
	for (int i = 0; i < 4; i++) {
		if (trilist[i].Hit(ray, t_min, t_max, hit_record)) {
			t_max = hit_record.t;
			hit_anything = true;
		}
	}

	return hit_anything;

}

bool Quadrilateral::BoundingBox(float t0, float t1, AABB& aabb)
{
	AABB tempbox;
	bool flag=trilist[0].BoundingBox(t0, t1,tempbox);
	if (!flag) return false;

	aabb = tempbox;

	for (int i = 1; i < 4; i++) {
		flag = trilist[i].BoundingBox(t0, t1, tempbox);
		if (!flag) return false;
		aabb = aabb.SurroundingBox(tempbox);
	}
	return true;
}
