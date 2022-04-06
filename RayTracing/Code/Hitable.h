#pragma once
#include "Ray.h"
#include "Material.h"
#include "AABB.h"

class Material;

//相交点位置与方向
struct Hit_Record {
	double t=0;
	Vector3 HitPoint;
	Vector3 NormalDirection;
	Material* mat_ptr=nullptr;
	double u = 0;
	double v = 0;
};

//可与光线相交物体
class HitableObject {
public:
	virtual bool Hit( Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  = 0;

	virtual bool BoundingBox(double t0, double t1, AABB& aabb) = 0;
};