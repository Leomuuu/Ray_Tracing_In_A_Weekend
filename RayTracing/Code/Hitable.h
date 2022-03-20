#pragma once
#include "Ray.h"

class Material;

//相交点位置与方向
struct Hit_Record {
	double t=0;
	Vector3 HitPoint;
	Vector3 NormalDirection;
};

//可与光线相交物体
class HitableObject {
public:
	virtual bool Hit( Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record)  = 0;
};