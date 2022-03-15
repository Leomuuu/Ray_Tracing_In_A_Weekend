#pragma once
#include "Hitable.h"

class Sphere :public HitableObject {

private:
	double radius;
	Vector3 center;

public:
	Sphere() :radius(0) {}

	Sphere(Vector3 cen, double r) :center(cen), radius(r) {}

	virtual bool Hit( Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  override;



};