#include "Sphere.h"
#include <cmath>

bool Sphere::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record) 
{
	Vector3 oc = ray.Start() - center;
	double a = ray.Direction().Dot(ray.Direction());
	double b = oc.Dot(ray.Direction());
	double c = oc.Dot(oc)-radius*radius;

	double discriminant = b * b - a * c;
	if (discriminant > 0) {
		double temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp<t_max && temp >t_min) {
			hit_record.t = temp;
			hit_record.HitPoint = ray.Point(temp);
			hit_record.NormalDirection = (hit_record.HitPoint - center).UnitVector();
			hit_record.mat_ptr = material;
			return true;
		}
		temp= (-b + sqrt(b * b - a * c)) / a;
		if (temp<t_max && temp >t_min) {
			hit_record.t = temp;
			hit_record.HitPoint = ray.Point(temp);
			hit_record.NormalDirection = (hit_record.HitPoint - center).UnitVector();
			hit_record.mat_ptr = material;
			return true;
		}
	
	}
	return false;
}