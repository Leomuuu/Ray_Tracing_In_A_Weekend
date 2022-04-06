#include <algorithm>
#include "Triangle.h"



bool Triangle::Hit(Ray& ray, double t_min, double t_max, Hit_Record& hit_record)
{
	Vector3 normal = (point2 - point1).Cross(point3 - point1).UnitVector();

	double np1start = normal.Dot(point1-ray.Start());
	double ndirection = normal.Dot(ray.Direction());

	if (ndirection <= 1e-20) return false;

	//光线与平面相交
	double temp = np1start / ndirection;

	if (temp <t_min || temp >t_max)  return false;

	Vector3 hitpoint = ray.Point(temp);

	if (hitpoint.X() > std::max({ point1.X(),point2.X(),point3.X() })) return false;
	if (hitpoint.X() < std::min({ point1.X(),point2.X(),point3.X() })) return false;
	if (hitpoint.Y() > std::max({ point1.Y(), point2.Y(), point3.Y() })) return false;
	if (hitpoint.Y() < std::min({ point1.Y(), point2.Y(), point3.Y() })) return false;
	if (hitpoint.Z() > std::max({ point1.Z(), point2.Z(), point3.Z() })) return false;
	if (hitpoint.Z() < std::min({ point1.Z(), point2.Z(), point3.Z() })) return false;

	Vector3 p1p = hitpoint - point1;
	Vector3 p2p = hitpoint - point2;
	Vector3 p3p = hitpoint - point3;
	Vector3 t1 = (point2 - point1).Cross(p1p).UnitVector();
	Vector3 t2 = (point3 - point2).Cross(p2p).UnitVector();
	Vector3 t3 = (point1 - point3).Cross(p3p).UnitVector();


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

bool Triangle::BoundingBox(double t0, double t1, AABB& aabb)
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