#pragma once
#include "Vector3.h"
#include "Ray.h"

inline double ffmax(double a, double b) { return (a > b) ? a : b; }
inline double ffmin(double a, double b) { return (a < b) ? a : b; }

class AABB {
public:
	Vector3 _min;
	Vector3 _max;

	AABB() {}
	AABB(Vector3& a, Vector3& b) { _min = a; _max = b; }

	bool Hit(Ray& ray, double tmin, double tmax);

	AABB SurroundingBox(AABB& aabb);

};