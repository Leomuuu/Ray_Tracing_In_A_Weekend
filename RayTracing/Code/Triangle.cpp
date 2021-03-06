#include <algorithm>
#include "Triangle.h"



bool Triangle::Hit(Ray& ray, float t_min, float t_max, Hit_Record& hit_record)
{
	Vector3 normal = ((point2 - point1).Cross(point3 - point1)).UnitVector();

	float np1start = normal.Dot(point1-ray.Start());
	float ndirection = normal.Dot(ray.Direction());

	if (abs(ndirection) <= 1e-20) return false;

	//光线与平面相交
	float temp = np1start / ndirection;

	if (temp <t_min || temp >t_max)  return false;

	Vector3 hitpoint = ray.Point(temp);

	Vector3 p1p = hitpoint - point1;
	Vector3 p2p = hitpoint - point2;
	Vector3 p3p = hitpoint - point3;
	Vector3 t1 = (point2 - point1).Cross(p1p);
	Vector3 t2 = (point3 - point2).Cross(p2p);
	Vector3 t3 = (point1 - point3).Cross(p3p);


	if (t1.Dot(normal) < 0) return false;
	if (t2.Dot(normal) < 0) return false;
	if (t3.Dot(normal) < 0) return false;


	//在三角形内
	hit_record.t = temp;
	hit_record.HitPoint = ray.Point(temp);
	hit_record.NormalDirection = normal;
	if (normal.Dot(ray.Direction()) > 0) hit_record.NormalDirection = -normal;
	hit_record.mat_ptr = material;
	return true;
	
}

bool Triangle::BoundingBox(float t0, float t1, AABB& aabb)
{
	Vector3 vmin(ffmin(ffmin(point1.X(),point2.X()),point3.X()),
		ffmin(ffmin(point1.Y(), point2.Y()), point3.Y()),
		ffmin(ffmin(point1.Z(), point2.Z()), point3.Z()));

	Vector3 vmax(ffmax(ffmax(point1.X(), point2.X()), point3.X()),
		ffmax(ffmax(point1.Y(), point2.Y()), point3.Y()),
		ffmax(ffmax(point1.Z(), point2.Z()), point3.Z()));

	aabb = AABB(vmin, vmax);
	return true;
}

float Triangle::pdf_value(Vector3& o, Vector3& v)
{
	Hit_Record rec;
	Ray r(o, v);
	if (this->Hit(r, 0.001, FLT_MAX, rec)) {
		float area = getarea();
		float distance_squared = rec.t * rec.t * v.Length() * v.Length();
		float cosine = fabs(v.Dot(rec.NormalDirection)) / v.Length();
		return distance_squared / (cosine * area);
	}
	return 0;
}

Vector3 Triangle::random(Vector3& o)
{
	float u1 = RANDfloat01;
	float u2 = RANDfloat01;

	Vector3 p = point1 * (1 - sqrt(u1)) + point2 * sqrt(u1) * (1 - u2) + point3 * sqrt(u1) * (u2);

	return p - o;
}

float Triangle::getarea()
{
	float a = (point1 - point2).Length();
	float b = (point2 - point3).Length();
	float c = (point3 - point1).Length();
	float p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}