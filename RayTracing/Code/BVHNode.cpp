#include "BVHNode.h"
#include <algorithm>

//按照某一轴比较包围盒的 顺序，用于排序
inline bool box_compare( HitableObject* a,  HitableObject* b, int axis) {
	AABB box_a;
	AABB box_b;

	return box_a._min[axis] < box_b._min[axis];
}


bool box_x_compare( HitableObject* a,  HitableObject* b) {
	return box_compare(a, b, 0);
}

bool box_y_compare( HitableObject* a,  HitableObject* b) {
	return box_compare(a, b, 1);
}

bool box_z_compare( HitableObject* a,  HitableObject* b) {
	return box_compare(a, b, 2);
}

BVHNode::BVHNode(std::vector<HitableObject*>& vec, int start, int end)
{
	int axis = rand() % 3;

	auto comparator = (axis == 0) ? box_x_compare
					: (axis == 1) ? box_y_compare
								  : box_z_compare;

	int veclen = end - start;

	if (veclen == 1) {
		left = right = vec[start];
	}
	else if (veclen == 2) {
		if (comparator(vec[start], vec[start + 1])) {
			left = vec[start];
			right = vec[start+1];
		}
		else {
			left = vec[start + 1];
			right = vec[start];
		}
	}
	else {
		std::sort(vec.begin() + start, vec.begin() + end, comparator);

		int mid = (start + end) / 2;
		left = new BVHNode(vec, start, mid);
		right = new BVHNode(vec, mid, end);
	}
	
	AABB box_left, box_right;
	left->BoundingBox(0, 0, box_left);
	right->BoundingBox(0, 0, box_right);

	box = box_left.SurroundingBox(box_right);
}

bool BVHNode::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{
	if (!box.Hit(ray, t_min, t_max))
		return false;

	bool hit_left = left->Hit(ray, t_min, t_max, hit_record);
	bool hit_right = right->Hit(ray, t_min,hit_left? hit_record.t:t_max, hit_record);

	return hit_left || hit_right;
}

bool BVHNode::BoundingBox(double t0, double t1, AABB& aabb)
{
	aabb = box;
	return true;
}