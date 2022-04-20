#include <cmath>
#include "Camera.h"
#include "Vector3.h"
#include "Material.h"

#define MYPI 3.141592653589793


//从一个小圆盘随机发出光线
Vector3 Random_In_Unit_Disk() {
	Vector3 p;
	do {
		float a = RANDfloat01;
		float b = RANDfloat01;


		p = Vector3(a, b, 0) * 2 - Vector3(1, 1, 0);
	} while (p.Dot(p) >= 1);

	return p;
}


NormalCamera::NormalCamera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect)
{
	float theta = vfov * MYPI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	origin = lookfrom;
	w = (lookfrom - lookat).UnitVector();
	u = vup.Cross(w).UnitVector();
	v = w.Cross(u);

	lower_left_corner = origin - u * half_width - v * half_height - w ;
	horizontal = u * 2 * half_width;
	vertical = v * 2 * half_height;
}


Ray NormalCamera::GetRay(float s, float t)
{
	return Ray(origin, lower_left_corner + horizontal * s + vertical * t - origin);

}

//vup 是向上的向量 用来得到摄像机的三个方向
DefocusBlurCamera::DefocusBlurCamera(Vector3 lookfrom, Vector3 lookat, Vector3 vup,
	float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	
	float theta = vfov * MYPI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	origin = lookfrom;
	w = (lookfrom - lookat).UnitVector();
	u = vup.Cross(w).UnitVector();
	v = w.Cross(u);

	lower_left_corner = origin - u*half_width*focus_dist- v*half_height*focus_dist - w*focus_dist;
	horizontal = u * 2 * half_width*focus_dist;
	vertical = v * 2 * half_height*focus_dist;

}
Ray DefocusBlurCamera::GetRay(float s, float t)
{
	Vector3 rd =  Random_In_Unit_Disk()*lens_radius ;
	Vector3 offset = u*rd.X()+v*rd.Y();
	return Ray(origin + offset, lower_left_corner + horizontal*s + vertical*t - origin - offset);

}

