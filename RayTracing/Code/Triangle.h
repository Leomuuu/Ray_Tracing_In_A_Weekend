#pragma once
#include "Hitable.h"
#include "Material.h"

class Triangle :public HitableObject {
private:
	Material* material;
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;

public:
	Triangle():material(nullptr) {}

	Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Material* m) :
		point1(p1), point2(p2), point3(p3),material(m) {}

	virtual bool Hit(Ray& ray, float t_min, float t_max,
		Hit_Record& hit_record)  override;

	virtual bool BoundingBox(float t0, float t1, AABB& aabb) override;


};