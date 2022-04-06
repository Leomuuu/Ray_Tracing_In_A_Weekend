#include <algorithm>
#include <cmath>
#include "Cylinder.h"


bool Cylinder::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{

	double startx = ray.Start().X() - x;
	double startz = ray.Start().Z() - z;
	double direcx = ray.Direction().X();
	double direcz = ray.Direction().Z();

	double a = direcx * direcx + direcz * direcz;
	double b = 2 * (direcz*startz + direcx*startx);
	double c = startx * startx + startz * startz-radius*radius;

	if (b * b - 4 * a * c <= 1e-20) return false;

	double temp = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	if (temp > t_min&& temp < t_max) {
		double y = ray.Start().Y() + temp * ray.Direction().Y();
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
	double temp1= (ymin - ray.Start().Y()) / ray.Direction().Y();
	double temp2= (ymax - ray.Start().Y()) / ray.Direction().Y();
	double tempmin= std::min(temp1, temp2);

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
		double yans = ray.Start().Y() + ray.Direction().Y() * tempmin;
		hit_record.NormalDirection = (yans < ray.Start().Y()) ? (Vector3(0, 1, 0)) : (Vector3(0, -1, 0));
		
		return true;
	}
	

	return false;
}
