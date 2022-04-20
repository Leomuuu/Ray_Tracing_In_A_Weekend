#include <algorithm>
#include <cmath>
#include "Cylinder.h"


bool Cylinder::Hit(Ray& ray, float t_min, float t_max, Hit_Record& hit_record)
{

	float startx = ray.Start().X() - x;
	float startz = ray.Start().Z() - z;
	float direcx = ray.Direction().X();
	float direcz = ray.Direction().Z();

	float a = direcx * direcx + direcz * direcz;
	float b = 2 * (direcz*startz + direcx*startx);
	float c = startx * startx + startz * startz-radius*radius;

	if (b * b - 4 * a * c <= 1e-20) return false;

	float temp = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	if (temp > t_min&& temp < t_max) {
		float y = ray.Start().Y() + temp * ray.Direction().Y();
		//在侧面与圆柱相交
		if (y > ymin && y < ymax) {
			hit_record.t = temp;
			hit_record.HitPoint = ray.Point(temp);
			hit_record.mat_ptr = materialaround;
			hit_record.NormalDirection = Vector3(hit_record.HitPoint.X() - x, 0, hit_record.HitPoint.Z() - z).UnitVector();
			return true;
		}
	}

	/*if (ray.Direction().UnitVector().Y() <= 1e-20) return false;*/

	//在上底面或下底面相交
	float temp1= (ymin - ray.Start().Y()) / ray.Direction().Y();
	float temp2= (ymax - ray.Start().Y()) / ray.Direction().Y();
	float tempmin= std::min(temp1, temp2);

	if (tempmin<t_min || tempmin>t_max) {
		tempmin = temp1 + temp2 - tempmin;
		if (tempmin<t_min || tempmin>t_max){
			return false;
		}
	}

	

	if (pow(ray.Point(tempmin).X() - x, 2) + pow(ray.Point(tempmin).Z() - z, 2) < radius * radius) {
		hit_record.t = tempmin;
		hit_record.HitPoint = ray.Point(tempmin);
		hit_record.mat_ptr = material;
		float yans = ray.Start().Y() + ray.Direction().Y() * tempmin;
		hit_record.NormalDirection = (yans < ray.Start().Y()) ? (Vector3(0, 1, 0)) : (Vector3(0, -1, 0));
		
		return true;
	}
	

	return false;
}

bool Cylinder::BoundingBox(float t0, float t1, AABB& aabb)
{
	Vector3 v1 =  Vector3(x-radius, ymin, z-radius);
	Vector3 v2 =  Vector3(x+radius, ymax, z+radius);
	aabb = AABB(v1, v2);
	return true;
}
