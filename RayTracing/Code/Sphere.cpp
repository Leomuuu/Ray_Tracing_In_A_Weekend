#include "Sphere.h"
#include <cmath>

bool Sphere::Hit(Ray& ray, float t_min, float t_max, Hit_Record& hit_record) 
{
	Vector3 oc = ray.Start() - center;
	float a = ray.Direction().Dot(ray.Direction());
	float b = oc.Dot(ray.Direction());
	float c = oc.Dot(oc)-radius*radius;

	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a;
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

bool Sphere::BoundingBox(float t0, float t1, AABB& aabb)
{
	Vector3 v1 = center - Vector3(radius, radius, radius);
	Vector3 v2 = center + Vector3(radius, radius, radius);
	aabb = AABB(v1,v2);
	return true;
}
float Sphere::pdf_value(Vector3& o, Vector3& v)
{
	Hit_Record rec;
	Ray r(o, v);
	if (this->Hit(r, 0.001, FLT_MAX, rec)) {
		float area = getarea()/2;
		float distance_squared = rec.t * rec.t * v.Length() * v.Length();
		float cosine = fabs(v.Dot(rec.NormalDirection)) / v.Length();
		return distance_squared / (cosine * area);
	}
	return 0;
}

Vector3 Sphere::random(Vector3& o)
{
	float e1 = RANDfloat01;
	float e2 = RANDfloat01;

	float theta = acos(1-2*e1);
	float phi = 2 * MPI * e2;

	return Vector3(radius*sin(theta)*cos(phi), radius*sin(theta)*sin(phi), radius*cos(theta));
}

float Sphere::getarea()
{
	return MPI * radius * radius;
}
