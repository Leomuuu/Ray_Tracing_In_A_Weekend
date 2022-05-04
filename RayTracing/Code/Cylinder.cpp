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

float Cylinder::pdf_value(Vector3& o, Vector3& v)
{
	Hit_Record rec;
	Ray r(o, v);
	if (this->Hit(r, 0.001, FLT_MAX, rec)) {
		float area = radius * radius * MPI;
		float distance_squared = rec.t*rec.t*v.Length() * v.Length();
		float cosine = fabs(v.Dot(rec.NormalDirection)) / v.Length();
		return distance_squared / (cosine * area);
	}
	return 0;
}

//随机采样
//Vector3 Cylinder::random(Vector3& o)
//{
//	float a = (RANDfloat01 - 0.5) * 2 * radius;
//	float b = (RANDfloat01 - 0.5) * 2 * radius;
//	while (a * a + b * b >= radius * radius) {
//		a = (RANDfloat01 - 0.5) * 2 * radius;
//		b = (RANDfloat01 - 0.5) * 2 * radius;
//	}
//	return Vector3(x+a, ymin , z+b) - o;
//
//}

//均匀采样
//Vector3 Cylinder::random(Vector3& o)
//{
//	//以xsample ysample为间隔
//	float xsample = 2;
//	float ysample = 2;
//	float dx = radius / xsample;
//	float dy = radius / ysample;
//
//	int xx = int((RANDfloat01 - 0.5) * 2 * xsample);
//	int yy = int((RANDfloat01 - 0.5) * 2 * ysample);
//
//	float a = float(xx) * dx + (xx>0)?(dx / 2):(-dx/2);
//	float b = float(yy) * dy + (yy>0)?(dy / 2):(-dy/2);
//
//	while (a * a + b * b >= radius * radius) {
//		xx = int((RANDfloat01 - 0.5) * 2 * xsample);
//		yy = int((RANDfloat01 - 0.5) * 2 * ysample);
//		a = float(xx) * dx + (xx > 0) ? (dx / 2) : (-dx / 2);
//		b = float(yy) * dy + (yy > 0) ? (dy / 2) : (-dy / 2);
//	}
//	return Vector3(x + a, ymin, z + b) - o;
//}

//蓝噪
Vector3 Cylinder::random(Vector3& o)
{
	//以xsample ysample为间隔
	float xsample = 10;
	float ysample = 10;
	float dx = radius / xsample;
	float dy = radius / ysample;

	int xx = int((RANDfloat01 - 0.5) * 2 * xsample);
	int yy = int((RANDfloat01 - 0.5) * 2 * ysample);

	float a = float(xx) * dx + RANDfloat01*((xx>0)?dx:-dx);
	float b = float(yy) * dy + RANDfloat01*((yy>0)?dy:-dy);

	while (a * a + b * b >= radius * radius) {
		xx = int((RANDfloat01 - 0.5) * 2 * xsample);
		yy = int((RANDfloat01 - 0.5) * 2 * ysample);
		a = float(xx) * dx + RANDfloat01 * ((xx > 0) ? dx : -dx);
		b = float(yy) * dy + RANDfloat01 * ((yy > 0) ? dy : -dy);
	}
	return Vector3(x + a, ymin, z + b) - o;
}