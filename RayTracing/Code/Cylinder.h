#pragma once
#include "Hitable.h"
#include "Material.h"

class Cylinder : public HitableObject {
private:

	Material* material; //上下底面材质
	Material* materialaround; //周围材质
	//默认圆柱处于xoz平面
	//圆心位置,半径
	float x, z;
	float radius;
	//高
	float ymin,ymax;


public:
	Cylinder(float _x,float _z,float _r,float _ymin,float _ymax, Material* m1,Material* m2) :
		material(m1),materialaround(m2),x(_x),z(_z),radius(_r),ymin(_ymin),ymax(_ymax)
	{}

	virtual bool Hit(Ray& ray, float t_min, float t_max,
		Hit_Record& hit_record)  override;

	virtual bool BoundingBox(float t0, float t1, AABB& aabb) override;

	virtual float pdf_value(Vector3& o, Vector3& v);
	virtual Vector3 random(Vector3& o);
	
};