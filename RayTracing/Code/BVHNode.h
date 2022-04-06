#pragma once
#include "Hitable.h"
#include "AABB.h"
#include "HitableList.h"
#include <vector>

class BVHNode:public HitableObject {
public:
	BVHNode() {};
	BVHNode(HitableList* list) :
		BVHNode(list->hitables,0, list->hitables.size()) {};
	BVHNode(std::vector<HitableObject*>& vec, int start, int end);

	virtual bool Hit(Ray& ray, double t_min, double t_max,
		Hit_Record& hit_record) override;
	virtual bool BoundingBox(double t0, double t1, AABB& aabb) override;

	HitableObject* left=nullptr;
	HitableObject* right=nullptr;
	AABB box;

};