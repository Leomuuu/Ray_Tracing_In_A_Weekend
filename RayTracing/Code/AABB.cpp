#include "AABB.h"

bool AABB::Hit(Ray& ray, float tmin, float tmax)
{
	for (int i = 0; i < 3; i++) {
		float t1 = (_min[i] - ray.Start()[i]) / ray.Direction()[i];
		float t2 = (_max[i] - ray.Start()[i]) / ray.Direction()[i];

		tmin =ffmax(ffmin(t1, t2),tmin);
		tmax =ffmin(ffmax(t1, t2),tmax);


		if (tmin > tmax) return false;

		return true;
	}
}

AABB AABB::SurroundingBox(AABB& aabb)
{
	Vector3 vmin(ffmin(aabb._min.X(), _min.X()),
		ffmin(aabb._min.Y(), _min.Y()),
		ffmin(aabb._min.Z(), _min.Z()));
	Vector3 vmax(ffmax(aabb._max.X(), _max.X()),
		ffmax(aabb._max.Y(), _max.Y()),
		ffmax(aabb._max.Z(), _max.Z()));

	return AABB(vmin, vmax);

}