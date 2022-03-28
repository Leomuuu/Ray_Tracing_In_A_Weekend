#pragma once
#include "Hitable.h"
#include "Material.h"

class Cylinder : public HitableObject {
private:

	Material* material; //上下底面材质
	Material* materialaround; //周围材质
	//默认圆柱处于xoz平面
	//圆心位置,半径
	double x, z;
	double radius;
	//高
	double ymin,ymax;
	//旋转
	double xangle;
	double yangle;
	double zangle;

	


public:
	Cylinder(double _x,double _z,double _r,double _ymin,double _ymax, Material* m1,Material* m2,
		double xa=0,double ya=0,double za=0) :
		material(m1),materialaround(m2),x(_x),z(_z),radius(_r),ymin(_ymin),ymax(_ymax),
		xangle(xa),yangle(ya),zangle(za)
	{}

	virtual bool Hit(Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  override;

};