#pragma once
#include "Triangle.h"

class Quadrilateral: public HitableObject {
private:
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 point4;
	Material* material;

public:
	Quadrilateral(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Material* m) :
		point1(p1), point2(p2), point3(p3), point4(p4), material(m) {}

	virtual bool Hit(Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  override;


};
