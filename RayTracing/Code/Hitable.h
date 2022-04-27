#pragma once
#include "Ray.h"
#include "Material.h"
#include "AABB.h"

class Material;

//相交点位置与方向
struct Hit_Record {
	float t=0;
	Vector3 HitPoint;
	Vector3 NormalDirection;
	Material* mat_ptr=nullptr;
	float u = 0;
	float v = 0;
};

//可与光线相交物体
class HitableObject {
public:
	virtual bool Hit( Ray& ray, float t_min, float t_max,
		Hit_Record& hit_record)  = 0;

	virtual bool BoundingBox(float t0, float t1, AABB& aabb) = 0;
	virtual float pdf_value(Vector3& o, Vector3& v) {
		return 0;
	}
	virtual Vector3 random(Vector3& o) {
		return Vector3(1, 0, 0);
	}

};