#pragma once
#include "Hitable.h"
#include "Material.h"

class Sphere :public HitableObject {

private:
	float radius;
	Vector3 center;
	Material* material;

public:

	Sphere(Vector3 cen, float r,Material* m) :center(cen), radius(r),material(m) {}

	virtual bool Hit( Ray& ray, float t_min, float t_max,
		Hit_Record& hit_record)  override;

	virtual bool BoundingBox(float t0, float t1, AABB& aabb) override;

};