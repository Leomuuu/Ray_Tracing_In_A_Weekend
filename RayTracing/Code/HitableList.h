#pragma once

#include "Hitable.h"
#include <vector>

class HitableList :public HitableObject{
public:
	std::vector<HitableObject*> hitables;

public:
	HitableList() {}
	HitableList(HitableList& hlist) {
		hitables = hlist.hitables;
	}
	virtual bool Hit(Ray& ray, float t_min, float t_max,
		Hit_Record& hit_record)  override;
	void AddHitables(HitableObject* object);

	virtual bool BoundingBox(float t0, float t1, AABB& aabb)override;

};