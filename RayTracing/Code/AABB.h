#pragma once
#include "Vector3.h"
#include "Ray.h"

inline float ffmax(float a, float b) { return (a > b) ? a : b; }
inline float ffmin(float a, float b) { return (a < b) ? a : b; }

class AABB {
public:
	Vector3 _min;
	Vector3 _max;

	AABB() {}
	AABB(Vector3& a, Vector3& b) { _min = a; _max = b; }

	bool Hit(Ray& ray, float tmin, float tmax);

	AABB SurroundingBox(AABB& aabb);

};