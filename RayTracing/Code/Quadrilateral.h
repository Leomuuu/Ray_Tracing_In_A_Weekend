#pragma once
#include "Triangle.h"

class Quadrilateral: public HitableObject {
private:
	
	Material* material;
	Triangle* trilist;

public:
	Quadrilateral(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, Material* m) :
		material(m) {
		trilist = new Triangle[4];
		trilist[0] = Triangle(point1, point2, point3, material);
		trilist[1] = Triangle(point1, point2, point4, material);
		trilist[2] = Triangle(point1, point3, point4, material);
		trilist[3] = Triangle(point2, point3, point4, material);

	}

	virtual bool Hit(Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  override;


};
