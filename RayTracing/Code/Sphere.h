#pragma once
#include "Hitable.h"
#include "Material.h"

class Sphere :public HitableObject {

private:
	double radius;
	Vector3 center;
	Material* material;

public:

	Sphere(Vector3 cen, double r,Material* m) :center(cen), radius(r),material(m) {}

	virtual bool Hit( Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  override;



};